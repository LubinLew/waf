# HTTP协议校验

> [nsfocus(绿盟)WAF: HTTP协议校验浅析](https://www.nsfocus.com.cn/upload/contents/2015/09/2015_09181716331196.pdf)
> [F5 WAF: Protocol Compliance](https://clouddocs.f5.com/training/community/waf/html/class3/module2/lab1/lab1.html)
> [Overview of BIG-IP ASM HTTP protocol compliance](https://support.f5.com/csp/article/K10280)
> [Fortinet(飞塔) WAF: Configuring an HTTP Protocol Constraint policy](https://help.fortinet.com/fadc/4-8-0/olh/Content/FortiADC/handbook/waf_protocol.htm)
> [barracuda(梭子鱼)WAF: Configuring Request Limits](https://campus.barracuda.com/product/webapplicationfirewall/doc/4259870/configuring-request-limits/)

|                     |                                                      |     |
| ------------------- | ---------------------------------------------------- | --- |
| URI最大长度             | 指统一资源标识符，即在浏览器地址栏中显示的地址                              |     |
| 请求参数最大个数            | URI 的查询字符串中所包含的参数个数                                  |     |
| 禁止异常锚点              | URI 中的锚点 (#) 不应该发送到服务器端，否则可能有安全隐患                    |     |
| 禁止异常主机头端口           | 主机头端口应与 TCP 连接端口一致，否则可能有安全隐患                         |     |
| 禁止非法域名              | 域名中只能由字母（ A～Z，a～z）、数字（0 ～ 9）和连接符（ ）组成，各级域名之间用实点（.）连接 |     |
| User-Agent最大长度      | 指 User-Agent 头部值的长度                                  |     |
| Cookie 最大长度         | 指整个 Cookie 头部值的长度                                    |     |
| Cookie 最大个数         | 指 Cookie 头部中包含的 Cookie 个数                            |     |
| Referer 最大长度        | 指 Referer 头部值的长度                                     |     |
| Accept 最大长度         | 指 Accept 头部值的长度                                      |     |
| Accept-Charset 最大长度 | 指 Accept-Charset 头部值的长度                              |     |
| Content-Length 最大长度 | 指 Content-Lengt 头部值的最大数字，实质上是 POST请求的最大 body 长度      |     |
|                     | POST请求时,Content-Length的值为0                           |     |
| 最大Range区间个数         | 指 Range 头部值中允许出现的分段区间个数                              |     |
| Range 最大跨度          | 指 Range 头部值中每个分段区间最大范围                               |     |
| HTTP头部最大个数          | 指 HTTP 头部个数                                          |     |
| HTTP头部字段名最大长度       | 指 HTTP 头部名的最大长度                                      |     |
| HTTP头部值最大长度         | 指 HTTP 头部值的最大长度                                      |     |
| 禁止重复HTTP头部          | 出现了重复的 HTTP 头部，有可能导致 WAF 被绕过                         |     |
| POST请求参数最大个数        | 指 POST 请求时 URI 的查询字符串中所包含的参数个数加上 HTTP 请求体中的参数个数      |     |
| 禁止重复参数              | 出现了重复的参数名称，有可能导致 WAF被绕过                              |     |
| 禁止二次URL编码           | 在 HTTP 会话中出现了 %25 且后面不是紧跟着两个十六进制值时，可能会导致绕过 WAF       |     |
| 是否清除异常%             | 当 URI 或参数值中包含‘%’，且后面不是紧跟着两个十六进制值时（如 %xy），可能会导致绕过 WAF |     |
| 是否清除空字符             | 当 URI 或参数值中包含 NULL 字符时 ( 如 \0，%00 等 )，
可能会导致绕过 WAF   |     |
|                     |                                                      |     |