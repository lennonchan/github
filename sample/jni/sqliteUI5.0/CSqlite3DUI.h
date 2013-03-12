/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：3D UI sqlite 文件 
/* 编 写 者：dabao
/* 编写日期：2012/04/28
/* 修改日期：2012/04/28
/* 其    他：无
/**********************************************************************************************************************/
#ifndef _Db_TCL_CSqlite3DUI_H__ 
#define _Db_TCL_CSqlite3DUI_H__ 
//*********************************************************************************************************************/
//定义引用库文件
#define  USE_STD
#ifdef USE_STD
#include <string>
#include <vector>

//#define  string  std::string
//#define  vector  std::vector

//using namespace std;
#else
#include "Tcl.h"
#include "tclArray.h"
#include "tclString.h"
using namespace tcl;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace scene;
#define  string  core::stringc
#define  vector  core::array
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include "sqlite3.h"
#ifdef __cplusplus
}
#endif
#ifdef WIN32
#include <Windows.h>
#define UNICODE
#else
#endif
#if defined(_UNICODE) || defined(UNICODE)
#pragma message("Unicode Selected")
#define _sqlite3_aggregate_context      sqlite3_aggregate_context
#define _sqlite3_aggregate_count        sqlite3_aggregate_count
#define _sqlite3_bind_blob              sqlite3_bind_blob
#define _sqlite3_bind_double            sqlite3_bind_double
#define _sqlite3_bind_int               sqlite3_bind_int
#define _sqlite3_bind_int64             sqlite3_bind_int64
#define _sqlite3_bind_null              sqlite3_bind_null
#define _sqlite3_bind_parameter_count   sqlite3_bind_parameter_count
#define _sqlite3_bind_parameter_index   sqlite3_bind_parameter_index
#define _sqlite3_bind_parameter_name    sqlite3_bind_parameter_name
#define _sqlite3_bind_text              sqlite3_bind_text16
#define _sqlite3_bind_text16            sqlite3_bind_text16
#define _sqlite3_busy_handler           sqlite3_busy_handler
#define _sqlite3_busy_timeout           sqlite3_busy_timeout
#define _sqlite3_changes                sqlite3_changes
#define _sqlite3_close                  sqlite3_close
#define _sqlite3_collation_needed       sqlite3_collation_needed16
#define _sqlite3_collation_needed16     sqlite3_collation_needed16
#define _sqlite3_column_blob            sqlite3_column_blob
#define _sqlite3_column_bytes           sqlite3_column_bytes16
#define _sqlite3_column_bytes16         sqlite3_column_bytes16
#define _sqlite3_column_count           sqlite3_column_count
#define _sqlite3_column_decltype        sqlite3_column_decltype16
#define _sqlite3_column_decltype16      sqlite3_column_decltype16
#define _sqlite3_column_double          sqlite3_column_double
#define _sqlite3_column_int             sqlite3_column_int
#define _sqlite3_column_int64           sqlite3_column_int64
#define _sqlite3_column_name            sqlite3_column_name16
#define _sqlite3_column_name16          sqlite3_column_name16
#define _sqlite3_column_text            sqlite3_column_text16
#define _sqlite3_column_text16          sqlite3_column_text16
#define _sqlite3_column_type            sqlite3_column_type
#define _sqlite3_commit_hook            sqlite3_commit_hook
#define _sqlite3_complete               sqlite3_complete16
#define _sqlite3_complete16             sqlite3_complete16
#define _sqlite3_create_collation       sqlite3_create_collation16
#define _sqlite3_create_collation16     sqlite3_create_collation16
#define _sqlite3_create_function        sqlite3_create_function16
#define _sqlite3_create_function16      sqlite3_create_function16
#define _sqlite3_data_count             sqlite3_data_count
#define _sqlite3_errcode                sqlite3_errcode
#define _sqlite3_errmsg                 sqlite3_errmsg16
#define _sqlite3_errmsg16               sqlite3_errmsg16
#define _sqlite3_exec                   sqlite3_exec
#define _sqlite3_finalize               sqlite3_finalize
#define _sqlite3_free                   sqlite3_free
#define _sqlite3_free_table             sqlite3_free_table
#define _sqlite3_get_table              sqlite3_get_table
#define _sqlite3_interrupt              sqlite3_interrupt
#define _sqlite3_last_insert_rowid      sqlite3_last_insert_rowid
#define _sqlite3_libversion             sqlite3_libversion
#define _sqlite3_mprintf                sqlite3_mprintf
#define _sqlite3_open                   sqlite3_open16
#define _sqlite3_open16                 sqlite3_open16
#define _sqlite3_prepare                sqlite3_prepare16
#define _sqlite3_prepare16              sqlite3_prepare16
#define _sqlite3_progress_handler       sqlite3_progress_handler
#define _sqlite3_reset                  sqlite3_reset
#define _sqlite3_result_blob            sqlite3_result_blob
#define _sqlite3_result_double          sqlite3_result_double
#define _sqlite3_result_error           sqlite3_result_error16
#define _sqlite3_result_error16         sqlite3_result_error16
#define _sqlite3_result_int             sqlite3_result_int
#define _sqlite3_result_int64           sqlite3_result_int64
#define _sqlite3_result_null            sqlite3_result_null
#define _sqlite3_result_text            sqlite3_result_text16
#define _sqlite3_result_text16          sqlite3_result_text16
#define _sqlite3_result_text16be        sqlite3_result_text16be
#define _sqlite3_result_text16le        sqlite3_result_text16le
#define _sqlite3_result_value           sqlite3_result_value
#define _sqlite3_set_authorizer         sqlite3_set_authorizer
#define _sqlite3_step                   sqlite3_step
#define _sqlite3_total_changes          sqlite3_total_changes
#define _sqlite3_trace                  sqlite3_trace
#define _sqlite3_user_data              sqlite3_user_data
#define _sqlite3_value_blob             sqlite3_value_blob
#define _sqlite3_value_bytes            sqlite3_value_bytes16
#define _sqlite3_value_bytes16          sqlite3_value_bytes16
#define _sqlite3_value_double           sqlite3_value_double
#define _sqlite3_value_int              sqlite3_value_int
#define _sqlite3_value_int64            sqlite3_value_int64
#define _sqlite3_value_text             sqlite3_value_text16
#define _sqlite3_value_text16           sqlite3_value_text16
#define _sqlite3_value_text16be         sqlite3_value_text16be
#define _sqlite3_value_text16le         sqlite3_value_text16le
#define _sqlite3_value_type             sqlite3_value_type
#define _sqlite3_vmprintf               sqlite3_vmprintf
#else
#pragma message("MCBS Selected")
#define _sqlite3_aggregate_context      sqlite3_aggregate_context
#define _sqlite3_aggregate_count        sqlite3_aggregate_count
#define _sqlite3_bind_blob              sqlite3_bind_blob
#define _sqlite3_bind_double            sqlite3_bind_double
#define _sqlite3_bind_int               sqlite3_bind_int
#define _sqlite3_bind_int64             sqlite3_bind_int64
#define _sqlite3_bind_null              sqlite3_bind_null
#define _sqlite3_bind_parameter_count   sqlite3_bind_parameter_count
#define _sqlite3_bind_parameter_index   sqlite3_bind_parameter_index
#define _sqlite3_bind_parameter_name    sqlite3_bind_parameter_name
#define _sqlite3_bind_text              sqlite3_bind_text
#define _sqlite3_bind_text16            sqlite3_bind_text16
#define _sqlite3_busy_handler           sqlite3_busy_handler
#define _sqlite3_busy_timeout           sqlite3_busy_timeout
#define _sqlite3_changes                sqlite3_changes
#define _sqlite3_close                  sqlite3_close
#define _sqlite3_collation_needed       sqlite3_collation_needed
#define _sqlite3_collation_needed16     sqlite3_collation_needed16
#define _sqlite3_column_blob            sqlite3_column_blob
#define _sqlite3_column_bytes           sqlite3_column_bytes
#define _sqlite3_column_bytes16         sqlite3_column_bytes16
#define _sqlite3_column_count           sqlite3_column_count
#define _sqlite3_column_decltype        sqlite3_column_decltype
#define _sqlite3_column_decltype16      sqlite3_column_decltype16
#define _sqlite3_column_double          sqlite3_column_double
#define _sqlite3_column_int             sqlite3_column_int
#define _sqlite3_column_int64           sqlite3_column_int64
#define _sqlite3_column_name            sqlite3_column_name
#define _sqlite3_column_name16          sqlite3_column_name16
#define _sqlite3_column_text            sqlite3_column_text
#define _sqlite3_column_text16          sqlite3_column_text16
#define _sqlite3_column_type            sqlite3_column_type
#define _sqlite3_commit_hook            sqlite3_commit_hook
#define _sqlite3_complete               sqlite3_complete
#define _sqlite3_complete16             sqlite3_complete16
#define _sqlite3_create_collation       sqlite3_create_collation
#define _sqlite3_create_collation16     sqlite3_create_collation16
#define _sqlite3_create_function        sqlite3_create_function
#define _sqlite3_create_function16      sqlite3_create_function16
#define _sqlite3_data_count             sqlite3_data_count
#define _sqlite3_errcode                sqlite3_errcode
#define _sqlite3_errmsg                 sqlite3_errmsg
#define _sqlite3_errmsg16               sqlite3_errmsg16
#define _sqlite3_exec                   sqlite3_exec
#define _sqlite3_finalize               sqlite3_finalize
#define _sqlite3_free                   sqlite3_free
#define _sqlite3_free_table             sqlite3_free_table
#define _sqlite3_get_table              sqlite3_get_table
#define _sqlite3_interrupt              sqlite3_interrupt
#define _sqlite3_last_insert_rowid      sqlite3_last_insert_rowid
#define _sqlite3_libversion             sqlite3_libversion
#define _sqlite3_mprintf                sqlite3_mprintf
#define _sqlite3_open                   sqlite3_open
#define _sqlite3_open16                 sqlite3_open16
#define _sqlite3_prepare                sqlite3_prepare
#define _sqlite3_prepare16              sqlite3_prepare16
#define _sqlite3_progress_handler       sqlite3_progress_handler
#define _sqlite3_reset                  sqlite3_reset
#define _sqlite3_result_blob            sqlite3_result_blob
#define _sqlite3_result_double          sqlite3_result_double
#define _sqlite3_result_error           sqlite3_result_error
#define _sqlite3_result_error16         sqlite3_result_error16
#define _sqlite3_result_int             sqlite3_result_int
#define _sqlite3_result_int64           sqlite3_result_int64
#define _sqlite3_result_null            sqlite3_result_null
#define _sqlite3_result_text            sqlite3_result_text
#define _sqlite3_result_text16          sqlite3_result_text16
#define _sqlite3_result_text16be        sqlite3_result_text16be
#define _sqlite3_result_text16le        sqlite3_result_text16le
#define _sqlite3_result_value           sqlite3_result_value
#define _sqlite3_set_authorizer         sqlite3_set_authorizer
#define _sqlite3_step                   sqlite3_step
#define _sqlite3_total_changes          sqlite3_total_changes
#define _sqlite3_trace                  sqlite3_trace
#define _sqlite3_user_data              sqlite3_user_data
#define _sqlite3_value_blob             sqlite3_value_blob
#define _sqlite3_value_bytes            sqlite3_value_bytes
#define _sqlite3_value_bytes16          sqlite3_value_bytes16
#define _sqlite3_value_double           sqlite3_value_double
#define _sqlite3_value_int              sqlite3_value_int
#define _sqlite3_value_int64            sqlite3_value_int64
#define _sqlite3_value_text             sqlite3_value_text
#define _sqlite3_value_text16           sqlite3_value_text16
#define _sqlite3_value_text16be         sqlite3_value_text16be
#define _sqlite3_value_text16le         sqlite3_value_text16le
#define _sqlite3_value_type             sqlite3_value_type
#define _sqlite3_vmprintf               sqlite3_vmprintf
#endif
typedef int (*Sqlite_CallBack)(void*,int,char**,char**);
namespace tcl
{

	typedef struct TableInfo
	{
		std::string TableName;

	}TableInfo;

	typedef struct SqLite_DataBase
	{
		sqlite3* pDataBase;
		sqlite3_stmt* pCurrentState;
		int BusyTimeoutMs;
		std::vector<TableInfo> TableInfos;

	}SqLite_DataBase;

	class CSqlite3UI
	{
	public:
		CSqlite3UI():m_CallBack(NULL)
		{}
		bool OpenSqliteDB(std::string dbPath,int &index);
		bool CloseSqliteDB();
		int  GetTableCount(int dataBaseIndex);
		std::vector<std::string> GetTableNames(SqLite_DataBase database);
		std::vector<std::string> ExecQuerrySql(int dataBaseIndex,std::string sql);
		bool ExecSql(int dataBaseIndex,std::string sql);
		~CSqlite3UI();
	private:
		int CheckSqlBeforeQuerry(int indexOfdataBase,std::string sql);
		std::string GetRowString(SqLite_DataBase database);
		int ColunmDataType(SqLite_DataBase database,int nCol);
		int GetColunmIndexByName(SqLite_DataBase database,char* name);
		char * ColunmName(SqLite_DataBase database,int nCol);
		double GetColunmValue2Double(SqLite_DataBase databse,int Column);
		int GetColumnValue2Int(SqLite_DataBase databse,int Column);
		char * GetColumnValue2Char(SqLite_DataBase database,int Column);
		std::vector<TableInfo> GetTabels(sqlite3* dataBase);
		std::vector<SqLite_DataBase> m_Databases;
		Sqlite_CallBack m_CallBack;
	};

	template<typename T,typename Contex>
	class IDataService
	{
	public:
		IDataService(){}
		virtual IDataService<T,Contex> * GetDataService(std::string filePath) = 0;
		virtual bool UpdateData(int nID,T new_value) =0;
		virtual bool DeleteData(int nID) =0;
		virtual bool AddData(T&  value) =0;
		virtual Contex GetDataByParentID(int parentID) =0;
		virtual Contex GetDataAll()=0;
		virtual Contex GetDataByPage(int PageIndex)=0;
		virtual ~IDataService(){}
		virtual Contex GetData(std::string item) = 0;

	};

	template<typename T,typename Contex>
	class CDataBaseService : public IDataService<T,Contex>
	{
	public:
		CDataBaseService(){}
		virtual IDataService<T,Contex> * GetDataService(std::string filePath)
		{
			m_CurrentIndex=0;
			if (m_SqliteDataBases.OpenSqliteDB(filePath,m_CurrentIndex))
			{
				return this;
			}
			return NULL;
		}
		virtual Contex GetDataByParentID(int parentID)
		{
			Contex data;
			return data;
		}
		virtual Contex GetDataAll()
		{
			Contex data;
			return data;
		}

		virtual bool UpdateData(int nID,T new_value)
		{
			return false;
		}
		
		virtual Contex GetDataByPage(int PageIndex)
		{
			Contex data;
			return data;
		}
		
		virtual bool DeleteData(int nID)
		{
			return false;
		}
		virtual bool AddData(T& value)
		{
			return false;
		}
		virtual ~CDataBaseService()
		{
			m_SqliteDataBases.CloseSqliteDB();
		}
		virtual Contex GetData(std::string item)
		{
			Contex data;
			return data;
		}
	private:
		CSqlite3UI m_SqliteDataBases;
		int m_CurrentIndex;
	};
}
#endif
