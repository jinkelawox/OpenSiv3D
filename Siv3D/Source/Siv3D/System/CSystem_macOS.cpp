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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../Siv3DEngine.hpp"
# include "CSystem_macOS.hpp"
# include "../Logger/ILogger.hpp"
# include "../CPU/ICPU.hpp"
# include "../ImageFormat/IImageFormat.hpp"
# include "../Window/IWindow.hpp"
# include "../Profiler/IProfiler.hpp"
# include "../DragDrop/IDragDrop.hpp"
# include "../Clipboard/IClipboard.hpp"
# include "../Cursor/ICursor.hpp"
# include "../Keyboard/IKeyboard.hpp"
# include "../Mouse/IMouse.hpp"
# include "../TextInput/ITextInput.hpp"
# include "../Codec/ICodec.hpp"
# include "../AudioFormat/IAudioFormat.hpp"
# include "../Audio/IAudio.hpp"
# include "../Graphics/IGraphics.hpp"
# include "../Font/IFont.hpp"
# include "../Print/IPrint.hpp"
# include "../ScreenCapture/IScreenCapture.hpp"
# include "../Effect/IEffect.hpp"
# include "../Script/IScript.hpp"

namespace s3d
{
	CSystem_macOS::CSystem_macOS()
	{

	}

	CSystem_macOS::~CSystem_macOS()
	{

	}

	bool CSystem_macOS::init()
	{
		if (!Siv3DEngine::GetLogger()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCPU()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetImageFormat()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetWindow()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetProfiler()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetDragDrop()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetClipboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCursor()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetKeyboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetMouse()->init())
		{
			return false;
		}
		
		if (!Siv3DEngine::GetTextInput()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCodec()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetAudioFormat()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetAudio()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetGraphics()->init())
		{
			return false;
		}
		
		Siv3DEngine::GetGraphics()->clear();

		if (!Siv3DEngine::GetFont()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetPrint()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetScreenCapture()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetEffect()->init())
		{
			return false;
		}
		
		if (!Siv3DEngine::GetScript()->init())
		{
			return false;
		}

		return true;
	}

	bool CSystem_macOS::update(bool clearGraphics)
	{
		m_previousEvent = m_event.exchange(0);

		if (const auto event = m_previousEvent & (WindowEvent::ExitFlag | m_exitEvent))
		{
			return false;
		}

		Siv3DEngine::GetPrint()->draw();

		if (!Siv3DEngine::GetGraphics()->flush(clearGraphics))
		{
			return false;
		}
		
		Siv3DEngine::GetProfiler()->endFrame();

		Siv3DEngine::GetGraphics()->present();

		Siv3DEngine::GetProfiler()->beginFrame();

		if (!Siv3DEngine::GetScreenCapture()->update())
		{
			return false;
		}

		if (!Siv3DEngine::GetProfiler()->reportAssetNextFrame())
		{
			return false;
		}

		++m_systemFrameCount;
		++m_userFrameCount;

		const uint64 currentNanoSec = Time::GetNanosec();
		m_currentDeltaTimeSec = m_previousFrameTimeNanosec ?
			(currentNanoSec - m_previousFrameTimeNanosec) / 1'000'000'000.0 : 0.0;
		m_previousFrameTimeNanosec = currentNanoSec;

		if (!Siv3DEngine::GetWindow()->update())
		{
			return false;
		}
		
		Siv3DEngine::GetGraphics()->clear();
		
		if (!Siv3DEngine::GetDragDrop()->update())
		{
			return false;
		}

		Siv3DEngine::GetCursor()->update();

		Siv3DEngine::GetKeyboard()->update();

		Siv3DEngine::GetMouse()->update();

		Siv3DEngine::GetTextInput()->update();
		
		return true;
	}

	void CSystem_macOS::reportEvent(const uint32 windowEventFlag)
	{
		m_event |= windowEventFlag;
	}

	void CSystem_macOS::setExitEvent(const uint32 windowEventFlag)
	{
		m_exitEvent = windowEventFlag;
	}

	uint32 CSystem_macOS::getPreviousEvent() const
	{
		return m_previousEvent;
	}

	uint64 CSystem_macOS::getSystemFrameCount() const noexcept
	{
		return m_systemFrameCount;
	}

	int32 CSystem_macOS::getUserFrameCount() const noexcept
	{
		return m_userFrameCount;
	}

	void CSystem_macOS::setUserFrameCount(const int32 count) noexcept
	{
		m_userFrameCount = count;
	}
	
	double CSystem_macOS::getDeltaTime() const noexcept
	{
		return m_currentDeltaTimeSec;
	}
}

# endif
