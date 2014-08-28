extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/class.hpp>
#include <luabind/function.hpp>
#include <luabind/functor.hpp>


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct glut_constants {};
struct gl_constants {};

namespace glut_bindings
{
	luabind::functor<void> displayfunc;

	void displayfunc_callback()
	{
		displayfunc();
	}

	void set_displayfunc(const luabind::functor<void>& fun)
	{
		glutDisplayFunc(&displayfunc_callback);
		displayfunc = fun;
	}

	luabind::functor<void> idlefunc;

	void idlefunc_callback()
	{
		idlefunc();
	}

	void set_idlefunc(const luabind::functor<void>& fun)
	{
		glutIdleFunc(&idlefunc_callback);
		idlefunc = fun;
	}


	luabind::functor<void> reshapefunc;

	void reshapefunc_callback(int w, int h)
	{
		reshapefunc(w,h);
	}

	void set_reshapefunc(const luabind::functor<void>& fun)
	{
		reshapefunc = fun;
	}

	luabind::functor<void> keyboardfunc;

	void keyboardfunc_callback(unsigned char key, int x, int y)
	{
		keyboardfunc(key,x,y);
	}

	void set_keyboardfunc(const luabind::functor<void>& fun)
	{
		glutKeyboardFunc(&keyboardfunc_callback);
		keyboardfunc = fun;
	}

	luabind::functor<void> mousefunc;

	void mousefunc_callback(int button, int state, int x, int y)
	{
		mousefunc(button, state, x, y);
	}

	void set_mousefunc(const luabind::functor<void>& fun)
	{
		mousefunc = fun;
	}
}

void bind_glut(lua_State* L)
{
	using namespace luabind;
	using namespace glut_bindings;

	open(L);
	
	function(L, "glutInitWindowSize", &glutInitWindowSize);
	function(L, "glutInitWindowPosition", &glutInitWindowPosition);
	function(L, "glutInitDisplayMode", &glutInitDisplayMode);

	class_<glut_constants>(L, "glut")
		.enum_("constants")
		[
			value("RGB", GLUT_RGB),
			value("RGBA", GLUT_RGBA),
			value("INDEX", GLUT_INDEX),
			value("SINGLE", GLUT_SINGLE),
			value("DOUBLE", GLUT_DOUBLE),
			value("DEPTH", GLUT_DEPTH),
			value("STENCIL", GLUT_STENCIL),
			value("LEFT_BUTTON", GLUT_LEFT_BUTTON),
			value("MIDDLE_BUTTON", GLUT_MIDDLE_BUTTON),
			value("RIGHT_BUTTON", GLUT_RIGHT_BUTTON),
			value("UP", GLUT_UP),
			value("DOWN", GLUT_DOWN),
			value("ELAPSED_TIME", GLUT_ELAPSED_TIME)
		];

	function(L, "glutCreateWindow", &glutCreateWindow);
	function(L, "glutDestroyWindow", &glutDestroyWindow);
	function(L, "glutFullScreen", &glutFullScreen);
	function(L, "glutDisplayFunc", &set_displayfunc);
	function(L, "glutKeyboardFunc", &set_keyboardfunc);
	function(L, "glutReshapeFunc", &set_reshapefunc);
	function(L, "glutIdleFunc", &set_idlefunc);
	function(L, "glutMainLoop", &glutMainLoop);
	function(L, "glutSwapBuffers", &glutSwapBuffers);
	function(L, "glutGet", &glutGet);
	function(L, "glutSolidSphere", &glutSolidSphere);
	function(L, "glutWireSphere", &glutWireSphere);
	function(L, "glutWireTeapot", &glutWireTeapot);
	function(L, "glutSolidTeapot", &glutSolidTeapot);

	// -- opengl

	class_<gl_constants>(L, "gl")
		.enum_("constants")
		[
			value("COLOR_BUFFER_BIT", GL_COLOR_BUFFER_BIT),
			value("DEPTH_BUFFER_BIT", GL_DEPTH_BUFFER_BIT),
			value("TRIANGLES", GL_TRIANGLES),
			value("MODELVIEW", GL_MODELVIEW),
			value("PROJECTION", GL_PROJECTION)
		];

	function(L, "glBegin", &glBegin);
	function(L, "glVertex3", &glVertex3f);
	function(L, "glEnd", &glEnd);
	function(L, "glClear", &glClear);
	function(L, "glPushMatrix", &glPushMatrix);
	function(L, "glPopMatrix", &glPopMatrix);
	function(L, "glRotate", &glRotatef);
	function(L, "glColor3", &glColor3f);
	function(L, "glColor4", &glColor4f);
	function(L, "glMatrixMode", &glMatrixMode);
	function(L, "glLoadIdentity", &glLoadIdentity);
	function(L, "glViewport", &glViewport);
	function(L, "glTranslate", &glTranslatef);

	// -- glu

	function(L, "gluPerspective", &gluPerspective);
}

int main()
{
	lua_State* L = lua_open();
	lua_baselibopen(L);
	lua_mathlibopen(L);
	bind_glut(L);

	int argc = 1;
	char* argv[1];
	argv[0] = "blabla";

	glutInit (&argc, argv);

	lua_dofile(L, "glut_bindings.lua");

	lua_close(L);
	return 0;
}

