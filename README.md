- [工具模块](#工具模块)
  - [日志模块](#日志模块)
    - [用法](#用法)
## 工具模块
### 日志模块
日志模块主要由log_event,log_format,logger,log_appender组成  
logger管理所有输出的appender,log_format用于日志格式,log_event描述日志内容,log_appender表示输出对象   
#### 用法
`ADD_APPENDER_STDOUT(level)`:添加标准输出为日志输出,level为最低输出日志等级  
`ADD_APPENDER_FILEOUT(level,filename)`:添加文件为日志输出,level为最低输出日志等级  
`DEL_APPENDER_FILEOUT(filename)`:取消一个文件的日志输出  
`DEL_APPENDER_STDOUT()`:取消标准输出的日志输出  
`LOG(level,str,...)`:向所有已经被添加的日志输出输出日志,level为日志等级,后面用法与printf一样  
