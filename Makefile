# ============================================
# CPU SIMÜLATÖRÜ MAKEFILE
# ============================================
# Klasör yapısı: src/ (.cpp) ve include/ (.h) ayrı

# DERLEYICI AYARLARI
# ============================================
CXX = g++

# CXXFLAGS: Derleme bayrakları
# -I include : Header dosyalarını include/ klasöründe ara
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I include

# HEDEF PROGRAM ADI
# ============================================
TARGET = computer

# KLASÖR YAPISI
# ============================================
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# KAYNAK DOSYALAR
# ============================================
# src/ klasöründeki tüm .cpp dosyaları
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Computer.cpp \
          $(SRC_DIR)/CPU.cpp \
          $(SRC_DIR)/Program.cpp

# OBJECT DOSYALARI
# ============================================
# obj/ klasörüne koyacağız
# src/main.cpp -> obj/main.o
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# HEADER DOSYALARI
# ============================================
# include/ klasöründeki tüm .h dosyaları
HEADERS = $(INC_DIR)/Computer.h \
          $(INC_DIR)/CPU.h \
          $(INC_DIR)/Program.h

# ============================================
# KURALLAR (RULES)
# ============================================

# DEFAULT HEDEF
all: $(OBJ_DIR) $(TARGET)

# OBJ KLASÖRÜNÜ OLUŞTUR
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "📁 obj/ klasörü oluşturuldu"

# ÇALIŞTIRILABILIR DOSYAYI OLUŞTURMA
$(TARGET): $(OBJECTS)
	@echo "🔗 Linking object files..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Build başarılı! Çalıştırılabilir dosya: $(TARGET)"
	@echo "📝 Kullanım: ./$(TARGET) <program_dosyası> <mod>"

# OBJECT DOSYALARINI OLUŞTURMA
# src/xxx.cpp -> obj/xxx.o
# Header değişikliklerini de takip et
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo "🔨 Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# TEMİZLEME
.PHONY: clean
clean:
	@echo "🧹 Temizleniyor..."
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "✅ Temizlik tamamlandı!"

# TAM TEMİZLİK
.PHONY: distclean
distclean: clean
	@echo "🧹 Derin temizlik yapılıyor..."
	rm -f *~ *.bak
	rm -f $(SRC_DIR)/*~ $(INC_DIR)/*~
	@echo "✅ Tüm geçici dosyalar silindi!"

# ÇALIŞTIRMA
# Örnek: make run ARGS="program.txt 1"
.PHONY: run
run: $(TARGET)
	@echo "▶️  Program çalıştırılıyor..."
	./$(TARGET) $(ARGS)

# DEBUG
.PHONY: debug
debug: $(TARGET)
	@echo "🐛 GDB başlatılıyor..."
	gdb ./$(TARGET)

# YARDIM
.PHONY: help
help:
	@echo "════════════════════════════════════════════════"
	@echo "  CPU SIMÜLATÖRÜ - MAKEFILE KOMUTLARI"
	@echo "════════════════════════════════════════════════"
	@echo ""
	@echo "Kullanılabilir komutlar:"
	@echo ""
	@echo "  make                  - Projeyi derler"
	@echo "  make clean            - Object ve executable dosyalarını siler"
	@echo "  make distclean        - Tüm geçici dosyaları siler"
	@echo "  make run ARGS='...'   - Programı derler ve çalıştırır"
	@echo "                          Örnek: make run ARGS='program.txt 1'"
	@echo "  make debug            - GDB debugger'ı başlatır"
	@echo "  make help             - Bu yardım mesajını gösterir"
	@echo "  make info             - Proje bilgilerini gösterir"
	@echo ""
	@echo "════════════════════════════════════════════════"
	@echo ""
	@echo "Klasör yapısı:"
	@echo "  src/       - Kaynak dosyaları (.cpp)"
	@echo "  include/   - Header dosyaları (.h)"
	@echo "  obj/       - Object dosyaları (.o) [otomatik oluşturulur]"
	@echo ""
	@echo "Örnek kullanım:"
	@echo "  make                         # Derle"
	@echo "  ./computer program.txt 1      # Çalıştır"
	@echo ""
	@echo "  VEYA tek komutta:"
	@echo "  make run ARGS='program.txt 1'"
	@echo ""

# PROJE BİLGİSİ
.PHONY: info
info:
	@echo "📊 Proje Bilgileri:"
	@echo "  Kaynak dosyalar: $(SOURCES)"
	@echo "  Object dosyalar: $(OBJECTS)"
	@echo "  Header dosyalar: $(HEADERS)"
	@echo "  Hedef program:   $(TARGET)"
	@echo "  Derleyici:       $(CXX)"
	@echo "  Bayraklar:       $(CXXFLAGS)"
