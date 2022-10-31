# MESI_cache-simulator
MESI协议有许多介绍，本节不再赘述，但是仍有一些细节问题需要处理。

第一，主存是否有MESI状态？

尽管在介绍MESI时，很常见地把主存也标为ESI中的某些状态，但是在[2]中，表示主存不需要状态标志位。那么，这应该是从硬件上考虑的，但在实际的科普介绍中，给主存标明状态有助于理解。

第二，MESI是哪种写策略？

[2]表示MESI使用Write-back，而且在多数情况下这是默认的。但在某些情况，MESI采用了Write-once。Write-once和Writ-back在MESI中有着不同的作用机制，这将导致它们在状态迁移和写回主存两方面有很大不同。

在Write-once中，不写入主存只发生在cache由E变为M时。例如，假定3个内核CPU0、CPU1、CPU2状态为I、S、S，CPU0请求写，则状态变为E、I、I，CPU0进行一次内存写；当3个内核状态为I，I，M时，CPU0请求写，则状态变为E、I、I。首先CPU2接受到总线写请求，便把数据写回内存并广播数据到总线，CPU0收到后，三者状态变为S、I、S，之后CPU0再对数据写，并且写回内存，此时变为E、I、I，一共发生两次内存写。网站[3]可以很好地展现上述MESI在Write-once下的变化，以及包括cache line替换的情况。

在Write-back中写入主存只有2种情况[4]。处于M状态的cache由于I状态cache发生read miss变为S，或者write miss变为I。其中，M状态cache变为S，它的cache line并没有被替换，但仍旧进行了写回，这应该是为了满足“S”状态的定义，不然主存中就没有对应的数据块了。令人困惑的是当M状态cache变为I时，它已经失效的副本仍旧被写回，而最新的数据块在别的cache中。那么失效副本有必要写回内存吗？在维基百科[5]和相关论文中都没有回答这个问题。我个人猜测，这是出于一种维持数据稳定的目的，内存至少保有一个最近有效的数据，那么即使最新的数据块出错（例如分支预测），也不必回滚到上次有效的状态，而是可以直接丢弃掉。MOESI中定义的O状态，可以很好地解决上述第一种需要写回的情况。在MOESI中，M状态的cache由于I状态cache发生read miss，前者会变O，后者变S，此时不发生写回。但是第二种情况，仍需要写回。而少了一种写回情况，MOESI的表现几乎处处好于MESI。

Write-once和Write-back在两种情况下的状态迁移有。cache为I或S发生本地写，Write-once下变为E，Write-back下变为M。

https://www.scss.tcd.ie/Jeremy.Jones/VivioJS/caches/MESIHelp.htm

https://en.wikipedia.org/wiki/MESI_protocol.

