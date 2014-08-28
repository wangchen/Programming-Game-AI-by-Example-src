// Copyright (c) 2003 Daniel Wallin and Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

extern "C"
{
	#include "lua.h"
}

#include <luabind/luabind.hpp>

int luabind::detail::free_functions::function_dispatcher(lua_State* L)
{
	function_rep* rep = static_cast<function_rep*>(lua_touserdata(L, lua_upvalueindex(1)));
	
	bool ambiguous = false;
	int min_match = std::numeric_limits<int>::max();
	int match_index = -1;
	bool ret;

#ifdef LUABIND_NO_ERROR_CHECKING
				
	if (rep->overloads().size() == 1)
	{
		match_index = 0;
	}
	else
	{

#endif
		int num_params = lua_gettop(L);
		ret = find_best_match(L, &rep->overloads().front(), rep->overloads().size(), sizeof(free_functions::overload_rep), ambiguous, min_match, match_index, num_params);

#ifdef LUABIND_NO_ERROR_CHECKING
	}

#else

	if (!ret)
	{
		// this bock is needed to make sure the std::string is destructed
		{
			std::string msg = "no match for function call '";
			msg += rep->name();
			msg += "' with the parameters (";
			msg += stack_content_by_name(L, 1);
			msg += ")\ncandidates are:\n";

			msg += get_overload_signatures(L, rep->overloads().begin(), rep->overloads().end(), rep->name());

			lua_pushstring(L, msg.c_str());
		}

		lua_error(L);
	}

	if (ambiguous)
	{
		// this bock is needed to make sure the std::string is destructed
		{
			std::string msg = "call of overloaded function '";
			msg += rep->name();
			msg += "(";
			msg += stack_content_by_name(L, 1);
			msg += ") is ambiguous\nnone of the overloads have a best conversion:";

			std::vector<const overload_rep_base*> candidates;
			find_exact_match(L, &rep->overloads().front(), rep->overloads().size(), sizeof(free_functions::overload_rep), min_match, num_params, candidates);

			msg += get_overload_signatures_candidates(L, candidates.begin(), candidates.end(), rep->name());

			lua_pushstring(L, msg.c_str());
		}
		lua_error(L);
	}
#endif
	const overload_rep& ov_rep = rep->overloads()[match_index];
	return ov_rep.call(L, ov_rep.fun);
}

