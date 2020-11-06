# code_snips

此仓库用于收集和管理学习过程中编写的代码片段，以便于日后回顾或者直接引用。
<br/><br/>目前主要包含以下内容：

1. 错误处理代码（01-error_handle）
2. 健壮的IO读写代码（02-robustIO）
3. 网络基础代码（03-network）:
    1. 01-raw_echo：最简单的基于socket API的echo server实现；
    2. 02-openfd：借助error handle与robustIO，并且用getaddrinfo()代替硬编码的IP和端口号，将由基本的socket API编写的监听和连接代码封装到open_clientfd()与open_listenfd()这两个函数中，并使用这两个函数编写了一个echo例程；
    3. 03-fork_echo:
    4. 04-thread_echo:
    5. 05-select_echo:
    