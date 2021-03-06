# WAF 部署模式

> [安全观察：浅谈WAF几种常见的部署模式](https://www.cnblogs.com/lhcbk/p/6799232.html)
> 
> [WAF基本原理与部署方式](https://blog.csdn.net/qq_38265137/article/details/106742893)

## WAF部署模式分类

根据WAF工作方式及原理不同可以分为四种工作模式：

- 透明代理模式(网桥代理模式)

- 反向代理模式(单臂模式)

- 路由代理模式(牵引模式)

- 端口镜像模式

前三种模式也被统称为在线模式，通常需要将WAF串行部署在WEB服务器前端，用于检测并阻断异常流量。端口镜像模式也称为离线模式，部署也相对简单，只需要将WAF旁路接在WEB服务器上游的交换机上，用于只检测异常流量。

### 透明代理模式

透明代理模式的工作原理是，当WEB客户端对服务器有连接请求时，TCP连接请求被WAF截取和监控。WAF偷偷的代理了WEB客户端和服务器之间的会话，将会话分成了两段，并基于桥模式进行转发。从WEB客户端的角度看，WEB客户端仍然是直接访问服务器，感知不到WAF的存在；从WAF工作转发原理看和透明网桥转发一样，因而称之为透明代理模式，又称之为透明桥模式。

### 反向代理模式

反向代理模式是指将真实服务器的地址映射到反向代理服务器上。此时代理服务器对外就表现为一个真实服务器。由于客户端访问的就是WAF，因此在WAF无需像其它模式（如透明和路由代理模式）一样需要采用特殊处理去劫持客户端与服务器的会话然后为其做透明代理。当代理服务器收到HTTP的请求报文后，将该请求转发给其对应的真实服务器。后台服务器接收到请求后将响应先发送给WAF设备，由WAF设备再将应答发送给客户端。这个过程和前面介绍的透明代理其工作原理类似，唯一区别就是透明代理客户端发出的请求的目的地址就直接是后台的服务器，所以透明代理工作方式不需要在WAF上配置IP映射关系。

### 路由代理模式

路由代理模式，它与网桥透明代理的唯一区别就是该代理工作在路由转发模式而非网桥模式，其它工作原理都一样。由于工作在路由（网关）模式因此需要为WAF的转发接口配置IP地址以及路由。

### 端口镜像模式

端口镜像模式工作时，WAF只对HTTP流量进行监控和报警，通常不进行拦截阻断。该模式需要使用交换机的端口镜像功能，也就是将交换机端口上的HTTP流量镜像一份给WAF。对于WAF而言，流量只进不出。

有一些WAF提供阻断功能，其原理就是向该条链接两端发送Reset包，断开链接，但是阻断是否成功取决于其发Reset包的速度，通常来说阻断率不是100%。

对于真实服务器是nginx/OpenResty 的情况来说, nginx在v1.13.4 版本提供了 mirror 功能，可以将请求流量镜像到 WAF，WAF必须对这种流程做特殊处理，不能将其再次发送的真实服务器（因为很多请求都有数据的操作）。这样WAF就能检测到请求的部分，响应的部分则无法检测。这种情况需要修改服务器配置，会增加服务器的带宽负载。



## BYPASS

通常WAF都有软件bypass 和 硬件 bypass。

硬件 bypass 适用于透明部署的情况。当WAF宕机或者重启，硬件bypass就会启动，其原理就是相同于将两个网口连接起来，相当于一根网线，当然启动的时候，之前处于连接状态的连接会断掉。

软件 bypass 除了镜像模式都试用。其原理就是不对流量进行任何检测，直接放行。通常用于网络排错， 或者WAF高负载需要放行一些新的链接等情况。软件 bypass 通常都是设置自动启停，当系统资源（CPU、内存等）不足时，则自动开启，当资源足够时，则自动关闭。



## 高可用

高可用的缩写为HA(High availability)。现实部署通常都会配置高可用, 防止WAF造成单点故障。高可用通常有2种，主备模式 和 主主模式。

主备模式是两台WAF一台主机一台备机, 平时只有主机工作，主备之间通过VRRP等协议进行通信，如果备机发现主机失联，则变身为主机，承载业务。根据抢占模式的设置，原主机恢复时的行为也不同，或成为备机， 或重新抢占再次成为主机。

主主模式则是两台WAF同时进行工作， 类似负载均衡。
