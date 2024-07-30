- [工具模块](#工具模块)
## 工具模块
### 日志
日志模块主要由log_event,log_format,logger,log_appender组成  
logger管理所有输出的appender,log_format用于日志格式,log_event描述日志内容,log_appender表示输出对象   
`ADD_APPENDER_STDOUT(level)`:添加标准输出为日志输出,level为最低输出日志等级  
`ADD_APPENDER_FILEOUT(level,filename)`:添加文件为日志输出,level为最低输出日志等级  
`DEL_APPENDER_FILEOUT(filename)`:取消一个文件的日志输出  
`DEL_APPENDER_STDOUT()`:取消标准输出的日志输出  
`LOG(level,str,...)`:向所有已经被添加的日志输出输出日志,level为日志等级,后面用法与printf一样  
### Pthread库封装
主要封装了pthread库的线程接口,模拟c++thread库的调用,便于后面封装线程池  
封装互斥锁,自旋锁,读写锁  
和`std:thread`差不多,锁有RAII机制的锁,也有手动锁  
### MySQL库封装
封装了MySQL库的接口同时保证访问数据库线程安全  
构造函数可传入用户名和密码和访问数据库名  
`string exec(const string& sql)`提供mysql语句的字符串返回执行结果,没有结果为空串,错误为"-1"  
## 数据管理模块
管理数据库用户的数据,提供对用户数据修改的接口  
`bool insert(tring& name,string& password)`新增用户  
`bool find_name(const string& name)`判断用户是否注册  
`user::ptr login(const string& name,const string& password)`用户登录,返回用户具体数据  
`bool add_count(const string& name)`修改用户的总对战场数  
`bool win(const string& name)`修改指定用户的总胜利场数  



