#ifndef SDLCLIB_TIME_H_INCLUDED
#define SDLCLIB_TIME_H_INCLUDED

class TSDLcTime
{
	private:
	
		Uint32 m_iTimeBegin;
		Uint32 m_iTimeNow;
		Uint32 m_iTimePrevious;
		Uint32 m_iTimeDelta;
		Uint32 m_iTimeFromBegin;
	
	public:
	
		static TSDLcTime & GetGlobalTime()
		{
			static TSDLcTime * pGlobalTime;
			if (pGlobalTime == nullptr)
			{
				pGlobalTime = new TSDLcTime;
			}
			return *pGlobalTime;
		}
	
		int GetTimeBegin() const
		{
			return m_iTimeBegin;
		}
	
		int GetTimeNow() const
		{
			return m_iTimeNow;
		}
	
		int GetTimePrevious() const
		{
			return m_iTimePrevious;
		}
	
		int GetTimeDelta() const
		{
			return m_iTimeDelta;
		}
	
		float GetTimeDeltaInSec() const
		{
			return m_iTimeDelta / 1000.0f;
		}
	
		int GetTimeFromBegin() const
		{
			return m_iTimeFromBegin;
		}
	
		void Initialize();
		void Update();
};


#endif
