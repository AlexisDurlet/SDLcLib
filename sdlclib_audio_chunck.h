#pragma once

class TSDLcAudioChunck
{
	private:

		Mix_Chunk * m_pChunck = nullptr;

	public:
		
		~TSDLcAudioChunck();
		void Load(const char * pFile);
		Mix_Chunk * GetChunck()
		{
			return m_pChunck;
		}
		void Destroy();
};

