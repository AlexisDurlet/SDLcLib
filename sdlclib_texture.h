#ifndef SDLCLIB_TEXTURE_H_INCLUDED
#define	SDLCLIB_TEXTURE_H_INCLUDED

class TSDLcTexture
{
	private:
	
		SDL_Texture * m_pTexture;
	
	public:
	
		TSDLcTexture();
		~TSDLcTexture();
	
		SDL_Texture * GetTexture() const 
		{
			return m_pTexture;
		}
	
		void Load(const char * pFileName);
		void Load(SDL_Surface * pSurface);
		void LoadCombine(const int iOutPutW, const int iOutPutH, const int iSurfacesNumber, SDL_Surface ** pSurfaces, SDL_Rect * pCopyOffsets, SDL_Rect * pPasteOffsets);
		//combine multiple surfaces, from first to last using the copy and paste offsets, into a  iOutPutW * iOutPutH surface and load the resulting surface into a texture.

		void Destroy();
};

#endif
