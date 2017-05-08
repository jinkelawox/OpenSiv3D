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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class PixelShader_GL
	{
	private:
		
		GLuint m_psProgram = 0;
		
		bool m_initialized = false;
		
	public:
		
		struct Null {};
		
		PixelShader_GL() = default;
		
		PixelShader_GL(Null)
		{
			m_initialized = true;
		}
		
		~PixelShader_GL()
		{
			if (m_psProgram)
			{
				::glDeleteProgram(m_psProgram);
			}
		}
		
		PixelShader_GL(const String& source)
		{
			const std::string sourceUTF8 = source.toUTF8();
			
			const char* pSource = sourceUTF8.c_str();
			
			m_psProgram = ::glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &pSource);
			
			GLint status = GL_FALSE;
			
			::glGetProgramiv(m_psProgram, GL_LINK_STATUS, &status);
			
			GLint logLen = 0;
			
			::glGetProgramiv(m_psProgram, GL_INFO_LOG_LENGTH, &logLen);
			
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				
				::glGetProgramInfoLog(m_psProgram, logLen, &logLen, &log[0]);
				
				//Log << CharacterSet::Widen(log);
			}
			
			if (status == GL_FALSE)
			{
				::glDeleteProgram(m_psProgram);
				
				m_psProgram = 0;
			}
			
			m_initialized = m_psProgram != 0;
		}
		
		bool isInitialized() const noexcept
		{
			return m_initialized;
		}
		
		GLint getProgram() const;
		
		ByteArrayView getView() const;
	};
}

# endif
