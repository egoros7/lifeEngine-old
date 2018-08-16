//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (��������� �����) ***
//					Copyright (C) 2017
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef BITSET_H
#define BITSET_H

#define COMPILING_LIBRARY
#include <DllGlobal.h>

//////////////////
// LIFEENGINE
//////////////////
#include <System\System.h>

namespace le
{	
	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief ����� ��� �������� ����� ����������, ������� ����
	/// ����������
	//////////////////////////////////////////////////////////////////////
	class DLL_API Bitset
	{
	public:

		//////////////////////////////////////////////////////////////////////
		/// \brief �����������
		//////////////////////////////////////////////////////////////////////
		Bitset();

		//////////////////////////////////////////////////////////////////////
		/// \brief ����������
		//////////////////////////////////////////////////////////////////////
		~Bitset();

		//////////////////////////////////////////////////////////////////////
		/// \brief �������� ������ �������� ������ �� �������, 
		/// ����� ������ ���� ������� ��������������� � ���
		///
		/// \param[in] Count ����������
		//////////////////////////////////////////////////////////////////////
		void Resize( int Count );

		//////////////////////////////////////////////////////////////////////
		/// \brief ������ ���
		//////////////////////////////////////////////////////////////////////
		void Set( int Byte );

		//////////////////////////////////////////////////////////////////////
		/// \brief �������� �������� ��������� ����
		///
		/// \return ���������� ������� ���
		//////////////////////////////////////////////////////////////////////
		int On( int Byte );

		//////////////////////////////////////////////////////////////////////
		/// \brief ���������� ��� � 0
		//////////////////////////////////////////////////////////////////////
		void Clear( int Byte );

		//////////////////////////////////////////////////////////////////////
		/// \brief ���������� ��� ���� � 0
		//////////////////////////////////////////////////////////////////////
		void ClearAll();

	private:

		unsigned int*		Bits;		///< ������ ����
		int					Size;		///< ������ �������
	};

	//-------------------------------------------------------------------------//
}

#endif // BITSET_H
