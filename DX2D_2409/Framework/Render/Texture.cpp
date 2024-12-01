#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file)
    : srv(srv), image(move(image)), file(file)
{
}

Texture::~Texture()
{
    srv->Release();
}

void Texture::PSSet(UINT slot)
{
    deviceContext->PSSetShaderResources(slot, 1, &srv);
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;
    CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    textures[file] = new Texture(srv, image, file);

    return textures[file];
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}
