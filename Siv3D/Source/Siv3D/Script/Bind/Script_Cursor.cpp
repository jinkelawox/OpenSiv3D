﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterCursor(asIScriptEngine *engine)
	{
		int r = 0;

		r = engine->SetDefaultNamespace("Cursor"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("Point Pos()", asFUNCTION(Cursor::Pos), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
