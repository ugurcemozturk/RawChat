# Recieve data from raw socket in C

## Getting Started
_*m.c*_       --> Recieve icinde kullanacagim, dosyaya veri yazip okuyan, bu verilerden linked list olusturan fonksiyonlari icerir.
_*macs.h*_    --> Dosyalara yazilacak verilerin data structures header'i.
_*macs.c*_    -> Veri yapilariyla kullanilacak fonksiyonlar.
_*packets.h*_ -> Ethernet paketine eklenecek custom made paketlerin tanimlandigi header file.

Hafta sonu sender olarak kullanacagim bir bilgisayar olmadigi icin daha once bir sende'in yolladigi datayi kopyalayip kullandim.

## Dummy data
### [Dest_MAC][Source_MAC][EthType][Name][Surname]

```
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x41, 0xfc,
	0xa5, 0xc4, 0xf2, 0x12, 0x34, 0x00, 0x6b, 0x69, 0x76, 0x61, 0x6e,								0x63, 0x00, 0x00, 0x00, 0x00, 0x63, 0x61, 0x6b, 0x6d, 0x61, 0x6b,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
```

### Compile and run

```
gcc -o rec recv.c macs.c utils.c
sudo ./rec
```



