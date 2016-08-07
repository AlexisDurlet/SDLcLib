#ifndef DBG_INFO_H_INCLUDED
#define	DBG_INFO_H_INCLUDED

class TSDLcDbgInfo
{
	private:

		TSDLcTextSprite * m_tTextDbg;

		enum ESDLcDbgDisplay
		{
			ESDLcDbgDisplay_On,
			ESDLcDbgDisplay_Off
		};

		ESDLcDbgDisplay m_eDisplayDbg;

		Uint32 m_iTextureNumber;
		Uint32 m_iSpriteNumber;
		Uint32 m_iDrawSpriteNumber;
		Uint32 m_iTextSpriteNumber;
		Uint32 m_iAudioChunckNumber;
		Uint32 m_iActiveSoundNumber;

		Uint32 m_iFrameRate;
		Uint32 m_iUpdateDuration;
		Uint32 m_iRenderDuration;

		static Uint32 m_iSDlcAllocations;
		static Uint32 m_iSDlcDeallocations;
		Uint32 m_iSDlcDeltaAllocations;

		static Uint32 m_iUserAllocations;
		static Uint32 m_iUserDeallocations;
		Uint32 m_iUserDeltaAllocations;
		

		TSDLcDbgInfo();
		~TSDLcDbgInfo();

	public:

		static TSDLcDbgInfo & GetInstance()
		{
			static TSDLcDbgInfo * pDbgInfo;
			if (pDbgInfo == nullptr)
			{
				pDbgInfo = new TSDLcDbgInfo;
			}
			return *pDbgInfo;
		}

		void IncrementTextureNb()
		{
			m_iTextureNumber++;
		}
		void DecrementTextureNb()
		{
			m_iTextureNumber--;
		}
		void IncrementSpriteNb()
		{
			m_iSpriteNumber++;
		}
		void DecrementSpriteNb()
		{
			m_iSpriteNumber--;
		}
		void IncrementDrawSpriteNb()
		{
			m_iDrawSpriteNumber++;
		}
		void DecrementDrawSpriteNb()
		{
			m_iDrawSpriteNumber--;
		}
		void IncrementTextSpriteNb()
		{
			m_iTextSpriteNumber++;
		}
		void DecrementTextSpriteNb()
		{
			m_iTextSpriteNumber--;
		}
		void IncrementAudioChunckNb()
		{
			m_iAudioChunckNumber++;
		}
		void DecrementAudioChunckNb()
		{
			m_iAudioChunckNumber--;
		}
		static void IncrementSDlcAllocations()
		{
			m_iSDlcAllocations++;
		}
		static void IncrementSDlcDeallocations()
		{
			m_iSDlcDeallocations++;
		}
		static void IncrementUserAllocations()
		{
			m_iUserAllocations++;
		}
		static void IncrementUserDeallocations()
		{
			m_iUserDeallocations++;
		}


		void Initialize();
		void Update();
		void Render();
};

#endif
