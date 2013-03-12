/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：CDataService<AppDataInfo,vector<AppDataInfo> > UI5.0
/* 编 写 者：dabao
/* 编写日期：2012/10/31
/* 修改日期：2012/10/31
/* 其    他：无
/**********************************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "CUI50DBService.h"

using std::vector;
using std::string;

namespace tcl
{
	template<typename T>
	string intTostring( T value)
	{
		return string("");
	}

	template<>
	string intTostring(int t)
	{
		char databuffer[128] ={0};
		sprintf(databuffer,"%d",t);
		return string(databuffer);
	}
	template<>
	string intTostring(double t)
	{
		char databuffer[128] ={0};
		sprintf(databuffer,"%f",t);
		return string(databuffer);
	}

    #define  TOSTR(value) intTostring(value)

	static vector<string> split(string str,string pattern);
	
	IDataService<AppDataInfo,vector<AppDataInfo> > * CDataService::GetDataService(string filePath)
	{
		m_CurrentIndex = 0;
		if (m_SqliteDataBases.OpenSqliteDB(filePath,m_CurrentIndex))
		{
			return this;
		}
		return NULL;
	}
	bool CDataService::UpdateData(int nID,AppDataInfo new_value)
	{
		bool ErrorCode = true;
		string BaseSql = "update ";
		BaseSql	+=m_TableName;
		BaseSql	+=" set ";
		BaseSql	+=" appName='"; BaseSql+=new_value.AppName; BaseSql +="',";
		BaseSql +=" packageName='"; BaseSql+=new_value.PackageName;BaseSql +="',";
		BaseSql +=" iconTextureID="; BaseSql+=TOSTR(new_value.appStartCount);BaseSql +=",";
		BaseSql +=" appNameTextureID="; BaseSql+=TOSTR(new_value.appNameTextureID);BaseSql +=",";
		BaseSql +=" appOrFolder=";BaseSql+=TOSTR(new_value.appOrFolder);BaseSql +=",";
		BaseSql +=" preInstallApp="; BaseSql+=TOSTR(new_value.preInstallApp);BaseSql +=",";
		BaseSql +=" parentFolderID=";BaseSql+=TOSTR(new_value.parentFolderID); BaseSql +=",";
		BaseSql +=" iconPosition="; BaseSql+=TOSTR(new_value.iconPositon);BaseSql +=",";
		BaseSql +=" folderEmpty="; BaseSql+=TOSTR(new_value.folderEmpty);BaseSql +=",";
		BaseSql +=" activityname='"; BaseSql+=new_value.activityname;BaseSql +="',";
		BaseSql +=" lengthratio=";BaseSql+=TOSTR(new_value.lengtharadio);BaseSql +=",";
        BaseSql +=" appEnglishName='"; BaseSql+=new_value.appenglishname; BaseSql +="' ";
		BaseSql +=" where appID =";
		BaseSql +=TOSTR(nID);
		ErrorCode = m_SqliteDataBases.ExecSql(m_CurrentIndex,BaseSql);
		return ErrorCode;
	}
	bool CDataService::DeleteData(int nID)
	{
		bool ErrorCode = true;
		string BaseSql = "delete from ";
		BaseSql	+=m_TableName;
		BaseSql	+=" where ";
		BaseSql	+=m_KeyName;
		BaseSql	+="=";
		BaseSql +=TOSTR(nID);
		ErrorCode = m_SqliteDataBases.ExecSql(m_CurrentIndex,BaseSql);
		return ErrorCode;
	}

	vector<AppDataInfo> CDataService::GetDataByPage(int PageIndex)
	{
		bool ErrorCode = true;
		string BaseSql = "SELECT * FROM ";
		BaseSql	+=m_TableName;
		BaseSql +=" WHERE parentFolderID = 0 ORDER BY iconPosition LIMIT ";
		if (PageIndex==0)
		{
			BaseSql +=" 0, 9";
		}
		else if(PageIndex > 0)
		{
			BaseSql +=(PageIndex-1)*18 + 9;
			BaseSql	+=", 18";
		}
		return GetData(BaseSql);
	}

	bool CDataService::AddData(AppDataInfo&  value)
	{
		bool ErrorCode = true;
		string BaseSql = "insert into ";
		BaseSql	+=m_TableName;
		BaseSql	+=" values(NULL,'";
		BaseSql	+=value.AppName; BaseSql +="','";
		BaseSql +=value.PackageName; BaseSql +="',";
		BaseSql +=TOSTR(value.appStartCount); BaseSql +=",";
		BaseSql +=TOSTR(value.appNameTextureID); BaseSql +=",";
		BaseSql +=TOSTR(value.appOrFolder); BaseSql +=",";
		BaseSql +=TOSTR(value.preInstallApp); BaseSql +=",";
		BaseSql +=TOSTR(value.parentFolderID); BaseSql +=",";
		BaseSql +=TOSTR(value.iconPositon); BaseSql +=",";
		BaseSql +=TOSTR(value.folderEmpty); BaseSql +=",'";
		BaseSql +=value.activityname; BaseSql +="',";
		BaseSql +=TOSTR(value.lengtharadio); BaseSql +=",'";
        BaseSql +=value.appenglishname; BaseSql +="'";
		BaseSql +=")";
		ErrorCode = m_SqliteDataBases.ExecSql(m_CurrentIndex,BaseSql);
		if (ErrorCode)
		{
			vector<string> MaxString = m_SqliteDataBases.ExecQuerrySql(m_CurrentIndex,"SELECT  max(appID) as MaxID FROM app_table ");
			if (MaxString.size())
			{
				value.AppID =  (int)::atof(MaxString[0].c_str());
			}
		}
		return ErrorCode;
	}
	CDataService::~CDataBaseService()
	{
		m_SqliteDataBases.CloseSqliteDB();
	}
	vector<AppDataInfo> CDataService::GetDataByParentID(int parentID)
	{
		string sqlData ="select * from ";
		sqlData += m_TableName;
		sqlData +="  where parentFolderID =";
		sqlData +=parentID;
		sqlData +=" ORDER BY iconPosition ASC";
		return GetData(sqlData);
	}

	void CDataService::GetDataByPos( int parentID, int iconPosition, AppDataInfo* pOutInfo )
	{
		string sqlData ="select * from ";
		sqlData += m_TableName;
		sqlData +="  where parentFolderID =";
		sqlData += parentID;
		sqlData +=" and iconPosition =";
		sqlData += iconPosition;
		vector<AppDataInfo> result = GetData( sqlData );
		if ( result.size() > 0 && pOutInfo )
		{
			*pOutInfo = result[0];
		}
	}

	void CDataService::GetFolderDataByName( const string& sName, AppDataInfo* pOutInfo )
	{
		string sqlData = "select * from ";
		sqlData += m_TableName;
		sqlData += " where appName = '";
		sqlData += sName;
		sqlData += "' and appOrFolder = 0";
		vector<AppDataInfo> result = GetData( sqlData );
		if ( result.size() > 0 && pOutInfo )
		{
			*pOutInfo = result[0];
		}
	}

    //根据包名和Activity名，查找AppInfo
    void CDataService::GetAppDataByName( const string& sPackageName, const string& sActivityName ,AppDataInfo* pOutInfo )
    {
        string sqlData = "select * from ";
        sqlData += m_TableName;
        sqlData += " where packageName = '";
        sqlData += sPackageName;
        sqlData += "'and activityname = '";
        sqlData += sActivityName;
        sqlData += "' and appOrFolder = 1";
        vector<AppDataInfo> result = GetData( sqlData );
        if ( result.size() > 0 && pOutInfo )
        {
            *pOutInfo = result[0];
        }
    }

	void CDataService::GetDataByID( int nID, AppDataInfo* pOutInfo )
	{
		string sqlData ="select * from ";
		sqlData += m_TableName;
		sqlData +="  where appID =";
		sqlData += nID;
		vector<AppDataInfo> result = GetData( sqlData );
		if ( result.size() > 0 && pOutInfo )
		{
			*pOutInfo = result[0];
		}
	}

	vector<AppDataInfo> CDataService::GetDataAll()
	{
		string sqlData ="select * from ";
		sqlData += m_TableName;
		sqlData +=" ORDER BY iconPosition ASC";
		return GetData(sqlData);
	}

	// add by dabao 2012-10-31 getdataALL by english name or click count
	// if ture return by englishName false return by click count
	vector<AppDataInfo> CDataService::GetDataAll(bool englishName)
	{
		string sqlData ="select * from ";
		sqlData += m_TableName;
		if (!englishName)
		{
			sqlData +=" ORDER BY iconTextureID DESC";
		}
		else 
		{
			sqlData +=" ORDER BY appEnglishName ASC";
		}
		return GetData(sqlData);
	}

	vector<AppDataInfo> CDataService::GetDataByPackageName(string packagename)
	{
		string sqlData = "select * from ";
		sqlData += m_TableName;
		sqlData += " where packageName = '";
		sqlData += packagename;
		sqlData += "' and appOrFolder = 1";
		sqlData +=" ORDER BY iconPosition DESC";
		return GetData( sqlData );
	}

	vector<AppDataInfo> CDataService::GetData(string item)
	{
		vector<AppDataInfo> data;
		vector<string> String_Data = m_SqliteDataBases.ExecQuerrySql(m_CurrentIndex,item);
		int Count = String_Data.size();
		if (Count)
		{	
			for (int i =0 ; i< Count; i++)
			{
				vector<string> temp;
				AppDataInfo appDataInfo;
#ifdef USE_STD
				temp = split(String_Data[i],"^|~");
#else
				String_Data[i].split(temp,"^|~",3);
#endif
				if (temp.size() != m_TableColumnCount)
				{
					LOGI("CDataService::GetData --- %s     ,temp.size()=%d\n",String_Data[i].c_str(),temp.size());
					continue;
				}
				appDataInfo.AppID = (int)::atof(temp[0].c_str());
				appDataInfo.AppName = temp[1].c_str();
				appDataInfo.PackageName = temp[2].c_str();
				appDataInfo.appStartCount = (int)atof(temp[3].c_str());
				appDataInfo.appNameTextureID = (int)atof(temp[4].c_str());
				appDataInfo.appOrFolder = (int)atof(temp[5].c_str());
				appDataInfo.preInstallApp = (int)atof(temp[6].c_str());
				appDataInfo.parentFolderID = (int)atof(temp[7].c_str());
				appDataInfo.iconPositon = (int)atof(temp[8].c_str());
				appDataInfo.folderEmpty = (int)atof(temp[9].c_str());
				appDataInfo.activityname = temp[10].c_str();
				appDataInfo.lengtharadio = atof(temp[11].c_str());
				appDataInfo.appenglishname = temp[12].c_str();
				data.push_back(appDataInfo);
			}
		}
		return data;
	}

#ifdef USE_STD
	vector<string> split(string str,string pattern)
	{
		 string::size_type pos;
		 vector<string> result;
		 int size=str.size();
		 for(int i=0; i<size; i++)
		 {
			 pos=str.find(pattern,i);
			 if(pos < size-1)
			 {
				 string s=str.substr(i,pos-i);
				 result.push_back(s);
				 i=pos+pattern.size()-1;	       
			 }	   
		 }
	    return result;
	}
#endif
}