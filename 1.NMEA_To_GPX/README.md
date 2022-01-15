# NMEA To GPX

主要功能在于接收GPS模块的输出信息，直接保存为一个GPX轨迹文件。

* 参考GPX和nmeliba解析代码；
* 由于原nmealib库只支持解析五条语句，现在大部分的GPS模块具有输出除了GPS之外的北斗和GNSS信息，本代码支持多语句解析，包括GPGGA,GPGSA,GPGSV,GPRMC,GPVTG,GPTXT,BDGSV,BDGSA,GNZDA,GNGLL,GNVTG,GNRMC,GNGGA语句。





# To Do

- [x] 移植到MCU上