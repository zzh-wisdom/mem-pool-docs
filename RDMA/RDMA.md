# RDMA

RDMA不同操作的相对性能高低由更底层的因素决定，如PCIe总线事务和NIC 架构细节。NIC的内部架构对于不同的厂商来说是专有且通常是机密的。[^guidelines-RDMA]

找到 RDMA 功能和应用程序之间的有效匹配是很重要的，因为
：RDMA 选项的最佳和最差选择的总吞吐量相差 70 倍，主机 CPU的开销相差 3.2 倍。[^guidelines-RDMA]

更重要的是，**RDMA没有一刀切的最佳使用方法**。



## 参考

[^guidelines-RDMA]: [A. K. M. Kaminsky and D. G. Andersen. Design guidelines for high performance rdma systems. In 2016 USENIX Annual Technical Conference, page 437, 2016.](https://www.usenix.org/conference/atc16/technical-sessions/presentation/kalia)

## 问题

1. MMIO与DMA的区别（它们都用到PCIe操作）
2. RDMA 读写涉及的MMIO和DMA
3. 