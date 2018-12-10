# XpSohijackDemo
借助xposed框架，hook so加载的过程中java层api，实现so的加载劫持，实现hook native

参考：
  https://bbs.pediy.com/thread-223699.htm
  https://github.com/ele7enxxh/Android-Inline-Hook
  

在看雪看了这篇文章(https://bbs.pediy.com/thread-223699.htm) 原作者的思路很棒，so劫持的思路不仅适用脱壳，将xposed 跟 inline hook相结合，
从而实现了android native hook。

inline hook 参考了 ele7enxxh/Android-Inline-Hook (https://github.com/ele7enxxh/Android-Inline-Hook)

用法：跟普通xposed模块用法相同，这只是个demo，方便起见 目标apk 与 xposed hook module 写在一起了，完全可以分开使用，修改代码so的加载路径即可（当然hook功能自己实现）。
