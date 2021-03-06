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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IShader.hpp"
# include "VertexShader_D3D11.hpp"
# include "PixelShader_D3D11.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		HINSTANCE m_d3dcompiler = nullptr;

		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

		AssetHandleManager<VertexShader::IDType, std::shared_ptr<VertexShader_D3D11>> m_vertexShaders{ S3DSTR("VertexShader") };

		AssetHandleManager<PixelShader::IDType, std::shared_ptr<PixelShader_D3D11>> m_pixelShaders{ S3DSTR("PixelShader") };

		VertexShader::IDType m_currentVS = VertexShader::IDType(-1);

		PixelShader::IDType m_currentPS = PixelShader::IDType(-1);

		Array<VertexShader> m_standardVSs;

		Array<PixelShader> m_standardPSs;

		bool compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target);
			
		bool compileHLSLToFile(const FilePath& hlsl, const FilePath& to, const char* entryPoint, const char* target);

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context);

		VertexShader::IDType createVS(ByteArray&& binary) override;

		VertexShader::IDType createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		
		VertexShader::IDType createVSFromSource(const String&, const Array<BindingPoint>&) override
		{
			// [Siv3D ToDo];
			return 0;
		}

		PixelShader::IDType createPS(ByteArray&& binary) override;

		PixelShader::IDType createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		
		PixelShader::IDType createPSFromSource(const String&, const Array<BindingPoint>&) override
		{
			// [Siv3D ToDo];
			return 0;
		}

		void releaseVS(VertexShader::IDType handleID) override;

		void releasePS(PixelShader::IDType handleID) override;

		ByteArrayView getBinaryViewVS(VertexShader::IDType handleID) override;

		ByteArrayView getBinaryViewPS(PixelShader::IDType handleID) override;

		const VertexShader& getStandardVS(size_t index) const override;

		const PixelShader& getStandardPS(size_t index) const override;

		void setVS(VertexShader::IDType handleID) override;

		void setPS(PixelShader::IDType handleID) override;
	};
}

# endif
