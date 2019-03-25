### Description
Printf4Debug

### Overview
STM32CubeMXで生成されたプロジェクト環境で, Printfを実現する. 

### Precondition
FreeRTOSの使用を前提とする. Queueバッファリング構造をとっているのでスレッドセーフ.

### HowToUse
Printf4Debug.hをincludeする. 
カーネル開始前に, PrintfInit関数を呼ぶ. 
メッセージを出したい場所で, Printf4Debug関数を呼ぶ. 

### 残存問題
1 UART2に直接依存しており, 一般化がまだできていない