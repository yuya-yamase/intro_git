■スタブ有り環境の説明
①
CANoeからCANメッセージ(0x3B1)を送ると、
VM0が受信して、受信したデータを各VMに送信する
　・VM0からVM1にメッセージ送信（CANID:0x3B1）
　・VM0からVM2にメッセージ送信（CANID:0x354）
　・VM0からVM3にメッセージ送信（CANID:0x1E3）
※上記処理は、Ecu_Intg_Callout.cに追加している。

②
Com_CbkTxReq()、Com_CbkTxAck()、Com_CbkRxAck()を空関数で用意して、
フック関数コールされることを確認できるようにしている。
※上記処理は、Ecu_Intg_Callout.cに追加している。

③
動作確認のために、VCan_URxIndication()を実装しています。
GWソフトチームでインテグする際に、以下パスに実装されてるVCan_URxIndication()を削除して、
GWソフトチームで新規実装してください。
パス：src\PE0VM0\BSW\Communication\oXCAN\scc\oxcan_aubif.c

