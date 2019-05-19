/*
 * BmpResourceLoader.cpp
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#include "BmpResourceLoader.h"
#include "BmpResourceExtraData.h"
#include "../debugging/Logger.h"

#include <memory> // shared_ptr
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <string> // string

using std::string;
using std::shared_ptr;
using boost::uintmax_t;

namespace base_game {

BmpResourceLoader::BmpResourceLoader() {
	logger::info("Create BmpResourceLoader");

}

BmpResourceLoader::~BmpResourceLoader() {
	logger::info("Destroy BmpResourceLoader");
}

string BmpResourceLoader::vGetPattern() {
	return "*.bmp";
}

bool BmpResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {
	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<BmpResourceExtraData> pExtraData = shared_ptr<
			BmpResourceExtraData>(new BmpResourceExtraData());
	pExtraData->init(rawBuffer, rawSize);
	handle->setExtraData(pExtraData);

	return true;
	/*
	 *
	 GameCodeApp::Renderer renderer = GameCodeApp::GetRendererImpl();
	 if (renderer == GameCodeApp::Renderer_D3D9)
	 {
	 shared_ptr<D3DTextureResourceExtraData9> extra = shared_ptr<D3DTextureResourceExtraData9>(GCC_NEW D3DTextureResourceExtraData9());

	 if ( FAILED ( D3DXCreateTextureFromFileInMemory( DXUTGetD3D9Device(), rawBuffer, rawSize, &extra->m_pTexture ) ) )
	 return false;
	 else
	 {
	 handle->SetExtra(shared_ptr<D3DTextureResourceExtraData9>(extra));
	 return true;
	 }
	 }
	 else if (renderer == GameCodeApp::Renderer_D3D11)
	 {
	 shared_ptr<D3DTextureResourceExtraData11> extra = shared_ptr<D3DTextureResourceExtraData11>(GCC_NEW D3DTextureResourceExtraData11());

	 // Load the Texture
	 if ( FAILED ( D3DX11CreateShaderResourceViewFromMemory( DXUTGetD3D11Device(), rawBuffer, rawSize, NULL, NULL, &extra->m_pTexture, NULL ) ) )
	 return false;

	 // Create the sample state
	 D3D11_SAMPLER_DESC sampDesc;
	 ZeroMemory( &sampDesc, sizeof(sampDesc) );
	 sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	 sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	 sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	 sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	 sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	 sampDesc.MinLOD = 0;
	 sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	 if( FAILED( DXUTGetD3D11Device()->CreateSamplerState( &sampDesc, &extra->m_pSamplerLinear ) ) )
	 return false;

	 handle->SetExtra(shared_ptr<D3DTextureResourceExtraData11>(extra));
	 return true;
	 }

	 GCC_ASSERT(0 && "Unsupported Renderer in TextureResourceLoader::VLoadResource");
	 return false;
	 */
}

} /* namespace base_game */
