/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：3D UI sqlite 
/* 编 写 者：dabao
/* 编写日期：2012/04/28
/* 修改日期：2012/04/28
/* 其    他：无
/**********************************************************************************************************************/
#include "CSqlite3DUI.h"

using std::vector;
using std::string;

namespace tcl
{
	bool CSqlite3UI::OpenSqliteDB(string dbPath,int &index)
	{
		SqLite_DataBase database;
		int ErrorCode = SQLITE_OK;
#if defined(_UNICODE) || defined(UNICODE)
		ErrorCode = sqlite3_open_v2(dbPath.c_str(), &database.pDataBase,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
#else 
		ErrorCode = sqlite3_open_v2(dbPath.c_str(), &database.pDataBase,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);

#endif
		if (ErrorCode == SQLITE_OK)
		{
			database.BusyTimeoutMs =100;
			database.pCurrentState = NULL;
			sqlite3_busy_timeout(database.pDataBase, database.BusyTimeoutMs);
			m_Databases.push_back(database);
			index = m_Databases.size() -1;
			m_Databases[index].TableInfos = GetTabels(database.pDataBase);	
		}
		else
		{
			sqlite3_close(database.pDataBase);
			database.pDataBase = NULL;
		}
		return !(bool)ErrorCode;
	}

	CSqlite3UI::~CSqlite3UI()
	{
		CloseSqliteDB();
		m_Databases.clear();
	}


	bool CSqlite3UI::CloseSqliteDB()
	{
		int Count = m_Databases.size();
		int Error_Code = SQLITE_OK;
		for (int i = 0; i< Count; i++)
		{
			if (m_Databases[i].pDataBase)
			{
				Error_Code |= sqlite3_finalize(m_Databases[i].pCurrentState);
				Error_Code |= _sqlite3_close(m_Databases[i].pDataBase);
			}
		}
		return !(bool)Error_Code;
	}

	vector<TableInfo> CSqlite3UI::GetTabels(sqlite3* dataBase)
	{
		vector<TableInfo> tables;
		if (dataBase)
		{
			int Count = m_Databases.size();
			int i =0;
			for (i =0 ; i< Count ; i++)
			{
				if (dataBase == m_Databases[i].pDataBase) break;
			}
			vector<string> stringInfo = ExecQuerrySql(i,"select name from sqlite_master where type='table'");
			int tableCount = stringInfo.size();
			for (int i =0 ; i< tableCount; i++)
			{
				TableInfo temp;
				temp.TableName = stringInfo[i];
				tables.push_back(temp);
			}
		}
		return tables;
	}

	int CSqlite3UI::CheckSqlBeforeQuerry(int indexOfdataBase,string sql)
	{
		int Count = m_Databases.size();
		int ErrorCode = SQLITE_OK;
		if (indexOfdataBase >=0 && indexOfdataBase < Count)
		{
			if (m_Databases[indexOfdataBase].pDataBase&& !m_Databases[indexOfdataBase].pCurrentState)
			{
#ifdef USE_STD
				ErrorCode = sqlite3_prepare_v2(m_Databases[indexOfdataBase].pDataBase, sql.c_str(), sql.length(), &m_Databases[indexOfdataBase].pCurrentState, NULL);
#else
				ErrorCode = sqlite3_prepare_v2(m_Databases[indexOfdataBase].pDataBase, sql.c_str(), sql.size(), &m_Databases[indexOfdataBase].pCurrentState, NULL);
#endif 
                if (ErrorCode == SQLITE_OK){
                    return SQLITE_OK;
                }
            }

			return ErrorCode;
		}
		else return ErrorCode = SQLITE_NULL;
	}

	double CSqlite3UI::GetColunmValue2Double(SqLite_DataBase database,int Column)
	{
		if (ColunmDataType(database,Column) == SQLITE_NULL) return NULL;
		else return _sqlite3_column_double(database.pCurrentState, Column);
	}

	int CSqlite3UI::GetColumnValue2Int(SqLite_DataBase database,int Column)
	{
		if (ColunmDataType(database,Column) == SQLITE_NULL) return NULL;
		else return _sqlite3_column_int(database.pCurrentState, Column);
	}

	char * CSqlite3UI::GetColumnValue2Char(SqLite_DataBase database,int Column)
	{
		if (ColunmDataType(database,Column) == SQLITE_NULL) return NULL;
		else return (char *)_sqlite3_column_text(database.pCurrentState, Column);
	}

	char *  CSqlite3UI::ColunmName(SqLite_DataBase database,int nCol)
	{
		if (database.pDataBase && database.pCurrentState)
		{
			int  Count = _sqlite3_column_count(database.pCurrentState);
			if (Count < 0 || nCol > Count-1) return NULL;
			else return (char *)_sqlite3_column_name(database.pCurrentState, nCol);
		}
		return NULL;
	}

	int CSqlite3UI::ColunmDataType(SqLite_DataBase database,int nCol)
	{
		if (database.pDataBase && database.pCurrentState)
		{
			int  Count = _sqlite3_column_count(database.pCurrentState);
			if (Count < 0 || nCol > Count-1) return -1;
			else return _sqlite3_column_type(database.pCurrentState, nCol);
		}
		return -1;
	}

	bool CSqlite3UI::ExecSql(int indexOfdataBase,string sql)
	{
		int ErrorCode = SQLITE_OK;
		int Count = m_Databases.size();
		if (indexOfdataBase < 0 && indexOfdataBase >= Count) return false;
#ifdef WIN32
		int wcsLen = MultiByteToWideChar(CP_ACP, NULL, sql.c_str(), strlen(sql.c_str()), NULL, 0);
		wchar_t* wszString = new wchar_t[wcsLen + 1];
		MultiByteToWideChar(CP_ACP, NULL, sql.c_str(), strlen(sql.c_str()), wszString, wcsLen);
		wszString[wcsLen]='\0';
		int ansiLen = WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		char* szAnsi = new char[ansiLen + 1];
		WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
		szAnsi[ansiLen] = '\0';
		sql ="";
		sql += szAnsi;
		delete wszString;
		delete szAnsi;
#endif 
		_sqlite3_exec(m_Databases[indexOfdataBase].pDataBase, "begin;", 0, 0, 0); 
		if (m_CallBack) ErrorCode = _sqlite3_exec(m_Databases[indexOfdataBase].pDataBase,sql.c_str(),m_CallBack,NULL,NULL);
		else ErrorCode = _sqlite3_exec(m_Databases[indexOfdataBase].pDataBase,sql.c_str(),NULL,NULL,NULL);
		if(ErrorCode == SQLITE_OK) _sqlite3_exec(m_Databases[indexOfdataBase].pDataBase, "commit;", 0, 0, 0);  	
		else _sqlite3_exec(m_Databases[indexOfdataBase].pDataBase, "rollback;", 0, 0, 0);
		return !(bool) ErrorCode;
	}

	vector<string> CSqlite3UI::ExecQuerrySql(int dataBaseIndex,string sql)
	{
		vector<string> data;
		if ( CheckSqlBeforeQuerry(dataBaseIndex,sql) == SQLITE_OK)
		{
			int nRet = 0;
			do
			{ 
				int nRet = _sqlite3_step(m_Databases[dataBaseIndex].pCurrentState);
				if (nRet == SQLITE_ROW) // at least 1 row
				{	
					string RowS = GetRowString(m_Databases[dataBaseIndex]);
					data.push_back(RowS);
					break;
                }else
				{
                    //LOGI("CSqlite3UI::ExecQuerrySql(),nRet=%d",nRet);
                }
			} while( nRet == SQLITE_SCHEMA );
			do 
			{

                if(m_Databases[dataBaseIndex].pCurrentState) {
                    nRet = _sqlite3_step(m_Databases[dataBaseIndex].pCurrentState);
                }

				if (nRet == SQLITE_DONE)
				{
                    if(m_Databases[dataBaseIndex].pCurrentState) {
					    nRet = _sqlite3_finalize(m_Databases[dataBaseIndex].pCurrentState);
                    }
					m_Databases[dataBaseIndex].pCurrentState = NULL;
					return data;
				}
				else if (nRet == SQLITE_ROW)
				{
					string RowS = GetRowString(m_Databases[dataBaseIndex]);
					data.push_back(RowS);
					continue;
				}
				else
				{
					if(m_Databases[dataBaseIndex].pCurrentState) {
                        nRet = _sqlite3_finalize(m_Databases[dataBaseIndex].pCurrentState);
                    }
					m_Databases[dataBaseIndex].pCurrentState = NULL;
					break;
				}
			} while (nRet == SQLITE_ROW);
		}
		return data;
	}

	string CSqlite3UI::GetRowString(SqLite_DataBase database)
	{
		int  Count = _sqlite3_column_count(database.pCurrentState);
		string RowStirng;
		char* NullChar ="";
		for (int i =0; i< Count; i++)
		{
			char * FidldString = (char *)sqlite3_column_text(database.pCurrentState, i);
			if(!FidldString) FidldString = NullChar;
#ifdef WIN32
			int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, FidldString, strlen(FidldString), NULL, 0);
			wchar_t* wszString = new wchar_t[wcsLen + 1];
			MultiByteToWideChar(CP_UTF8, NULL, FidldString, strlen(FidldString), wszString, wcsLen);
			wszString[wcsLen]='\0';
			int ansiLen = WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
			char* szAnsi = new char[ansiLen + 1];
			WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
			szAnsi[ansiLen] = '\0';
			RowStirng += szAnsi;
			RowStirng += "^|~";
			delete wszString;
			delete szAnsi;
#else
			RowStirng += FidldString;
			RowStirng += "^|~";
#endif

		}
		return RowStirng;
	}

	int CSqlite3UI::GetTableCount(int dataBaseIndex)
	{
		int ResultCode = 0;
		int Count = m_Databases.size();
		if (Count && dataBaseIndex >-1 && dataBaseIndex < Count)
		{
			ResultCode = m_Databases[dataBaseIndex].TableInfos.size();
		}
		return ResultCode;
	}
}
