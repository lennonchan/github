/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：CDataBaseService<AppDataInfo,std::vector<AppDataInfo> > 特例化为UI5.0项目服务 
/* 编 写 者：dabao
/* 编写日期：2012/10/31
/* 修改日期：2012/10/31
/* 其    他：无
/**********************************************************************************************************************/
#ifndef _Db_TCL_CDataBaseService_H__ 
#define _Db_TCL_CDataBaseService_H__ 
//*********************************************************************************************************************/
#include "CSqlite3DUI.h"
struct SAPPDATA;

#ifndef WIN32
#define LOGI(...)
#else
#define LOGI(...)
#endif

namespace tcl
{
	typedef struct AppDataInfo
	{
		int AppID;
		std::string AppName;
		std::string PackageName;
		int IconTextureID;
		int appNameTextureID;
		int appOrFolder;
		int preInstallApp;
		int parentFolderID;		
		int iconPositon;		//FolderID<<8|indexID
		int folderEmpty;
		std::string activityname;
		double lengtharadio;
		std::string appenglishname;
		int appStartCount;
		AppDataInfo()
			: AppID( -1 ), AppName( "" ), PackageName( "" )
			, IconTextureID( -1 ), appNameTextureID( -1 )
			, appOrFolder( 1 ), preInstallApp( 0 ), parentFolderID( 0 )
			, iconPositon( 0 ), folderEmpty( 1 ), activityname( "" )
			, lengtharadio( 1.0f )
			, appenglishname("") ,appStartCount(0)
		{

		}
	}AppDataInfo;

	template<>
	class CDataBaseService<AppDataInfo,std::vector<AppDataInfo> > : public IDataService<AppDataInfo,std::vector<AppDataInfo> >
	{

	public:
		CDataBaseService(): m_TableName("app_table"),m_KeyName("appID"),m_TableColumnCount(13)
		{
		}
		virtual IDataService<AppDataInfo,std::vector<AppDataInfo> > * GetDataService(std::string filePath);
		virtual bool UpdateData(int nID,AppDataInfo new_value);
		virtual bool DeleteData(int nID);
		virtual std::vector<AppDataInfo> GetDataByPage(int PageIndex);		
		virtual bool AddData(AppDataInfo&  value);
		virtual ~CDataBaseService();
		virtual std::vector<AppDataInfo> GetDataByParentID(int parentID);
		virtual std::vector<AppDataInfo> GetDataAll();
		virtual std::vector<AppDataInfo> GetDataAll(bool englishName);
		virtual std::vector<AppDataInfo> GetData(std::string item);
		virtual std::vector<AppDataInfo> GetDataByPackageName(std::string packagename);
		virtual void GetDataByPos( int parentID, int iconPosition, AppDataInfo* pOutInfo );
		virtual void GetDataByID( int nID, AppDataInfo* pOutInfo );
		virtual void GetFolderDataByName( const std::string& sName, AppDataInfo* pOutInfo );
		virtual void GetAppDataByName( const std::string& sPackageName, const std::string& sActivityName ,AppDataInfo* pOutInfo );
		//bool UpdateUsedData( const SAPPDATA& data );
	private:
		CSqlite3UI m_SqliteDataBases;
		int m_CurrentIndex;
		std::string m_TableName;
		std::string m_KeyName;
		int m_TableColumnCount;
	};

	typedef CDataBaseService<AppDataInfo,std::vector<AppDataInfo> > CDataService;
}
#endif
