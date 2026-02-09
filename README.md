# CPU Simülatörü 🖥️

Basit bir CPU simülatörü projesi. Assembly benzeri komutlarla temel işlemler gerçekleştiren, register'lar ve bellek yönetimine sahip bir sanal işlemci.

## 📋 Özellikler

- **6 adet register** (R1-R6)
- **100 byte bellek** alanı
- **8 farklı komut** desteği
- **3 farklı çalışma modu**
- Dosyadan program yükleme
- Interaktif input alma

## 🚀 Kurulum

### Gereksinimler
- C++ derleyici (g++ önerilir)
- Make (opsiyonel)

### Derleme

**Make kullanarak (önerilir):**
```bash
make
```

**Manuel derleme:**
```bash
g++ -I include -Wall -Wextra -std=c++11 -o computer src/main.cpp src/Computer.cpp src/CPU.cpp src/Program.cpp
```

## 💻 Kullanım

```bash
./computer <program_dosyası> <mod>
```

### Modlar:
- **0**: Sadece program çalıştır (çıktı gösterme)
- **1**: Her komuttan sonra register'ları göster
- **2**: Her komuttan sonra register'ları ve belleği göster

### Örnek:
```bash
./computer program.txt 1
```

## 📖 Desteklenen Komutlar

| Komut | Açıklama | Örnek |
|-------|----------|-------|
| `MOV` | Değer taşıma | `MOV R1, 5` |
| `ADD` | Toplama | `ADD R1, R2` |
| `SUB` | Çıkarma | `SUB R1, 10` |
| `JMP` | Koşulsuz/Koşullu atlama | `JMP 5` veya `JMP R1, 5` |
| `JPN` | Negatif/sıfırsa atla | `JPN R1, 3` |
| `PRN` | Yazdır | `PRN R1` |
| `INP` | Kullanıcıdan input al | `INP R1` |
| `HLT` | Programı durdur | `HLT` |

## 📝 Operand Türleri

- **Register**: `R1`, `R2`, ..., `R6`
- **Sabit değer**: `5`, `-10`, `100`
- **Bellek adresi**: `#0`, `#15`, `#99`

## 📄 Program Dosyası Formatı

```assembly
; Bu bir yorum satırıdır
MOV R1, 10      ; R1'e 10 değerini ata
MOV R2, 5       ; R2'ye 5 değerini ata
ADD R1, R2      ; R1 = R1 + R2 (sonuç: 15)
PRN R1          ; R1'i ekrana yazdır
HLT             ; Programı durdur
```

## 🏗️ Proje Yapısı

```
Custom-ISA-CPU/
├── src/                # Kaynak dosyaları (.cpp)
│   ├── main.cpp
│   ├── Computer.cpp
│   ├── CPU.cpp
│   └── Program.cpp
├── include/            # Header dosyaları (.h)
│   ├── Computer.h
│   ├── CPU.h
│   └── Program.h
├── obj/                # Object dosyaları (derleme sonrası, otomatik)
├── Makefile            # Derleme scripti
├── .gitignore          # Git ignore dosyası
└── README.md           # Bu dosya
```

## 🎯 Örnek Programlar

### 1. Basit Toplama
```assembly
MOV R1, 10
MOV R2, 20
ADD R1, R2
PRN R1
HLT
```

**Çıktı:**
```
MOV R1, 10 - R1=10, R2=0, R3=0, R4=0, R5=0, R6=0
MOV R2, 20 - R1=10, R2=20, R3=0, R4=0, R5=0, R6=0
ADD R1, R2 - R1=30, R2=20, R3=0, R4=0, R5=0, R6=0
30
PRN R1 - R1=30, R2=20, R3=0, R4=0, R5=0, R6=0
HLT - R1=30, R2=20, R3=0, R4=0, R5=0, R6=0
```

### 2. Döngü ile Sayma
```assembly
MOV R1, 1       ; Sayaç = 1
MOV R2, 5       ; Maksimum değer = 5
PRN R1          ; Mevcut sayıyı yazdır
ADD R1, 1       ; Sayacı 1 arttır
SUB R2, 1       ; Maksimum değeri 1 azalt
JPN R2, 3       ; Eğer R2 <= 0 ise 3. satıra (PRN) git
HLT
```

### 3. Bellek Kullanımı
```assembly
MOV R1, 42      ; R1 = 42
MOV #0, R1      ; Belleğin 0. adresine R1'i yaz
MOV #1, 100     ; Belleğin 1. adresine 100 yaz
MOV R2, #0      ; Belleğin 0. adresinden R2'ye oku
PRN R2          ; R2'yi yazdır (42)
MOV R3, #1      ; Belleğin 1. adresinden R3'e oku
PRN R3          ; R3'ü yazdır (100)
HLT
```

## 🛠️ Make Komutları

| Komut | Açıklama |
|-------|----------|
| `make` | Projeyi derle |
| `make clean` | Derlenmiş dosyaları sil |
| `make run ARGS='prog.txt 1'` | Derle ve çalıştır |
| `make debug` | GDB debugger başlat |
| `make help` | Yardım menüsü göster |
| `make info` | Proje bilgilerini göster |

### Kullanım Örnekleri

```bash
# Projeyi derle
make

# Temizle ve yeniden derle
make clean
make

# Bir program çalıştır
make run ARGS='test.txt 1'

# Debug modda çalıştır
make debug
```

## 🧹 Temizleme

```bash
# Object ve executable dosyalarını sil
make clean

# Tüm geçici dosyaları da sil
make distclean
```

## 📚 Teknik Detaylar

- **Register boyutu**: 32-bit integer
- **Bellek boyutu**: 100 byte (unsigned char)
- **Maksimum program uzunluğu**: 500 satır
- **Register aralığı**: R1-R6
- **Bellek aralığı**: #0-#99
- **Derleyici**: g++ (C++11 standardı)

## ⚠️ Sınırlamalar

- Maksimum 6 register
- Bellek adresleri 0-99 arası
- Program dosyası maksimum 500 satır
- Tamsayı işlemleri (float/double desteklenmez)

## 🐛 Hata Ayıklama

### Derleme Hataları
```bash
# Detaylı bilgi için
make clean
make

# Header dosyaları bulunamazsa
# include/ klasörünün doğru yerde olduğundan emin olun
```

### Çalışma Zamanı Hataları
```bash
# GDB ile debug
make debug
(gdb) run program.txt 1
(gdb) break CPU::execute
(gdb) continue
```

## 🤝 Katkıda Bulunma

1. Fork yapın
2. Feature branch oluşturun (`git checkout -b feature/YeniOzellik`)
3. Commit yapın (`git commit -m 'Yeni özellik eklendi'`)
4. Push yapın (`git push origin feature/YeniOzellik`)
5. Pull Request açın

## 📝 Lisans

Bu proje eğitim amaçlıdır - CSE241 Nesne Yönelimli Programlama dersi kapsamında geliştirilmiştir.

## 👨‍💻 Geliştirici

Gebze Teknik Üniversitesi - Bilgisayar Mühendisliği

---

**Not**: Herhangi bir hata veya öneri için issue açabilirsiniz.
