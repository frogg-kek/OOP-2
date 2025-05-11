CXX = g++
CXXFLAGS = -std=c++20 -Wall -O3

TARGET = kursiokai
APP_NAME = Kursiokai.app
APP_DIR = $(APP_NAME)/Contents
MACOS_DIR = $(APP_DIR)/MacOS
RESOURCES_DIR = $(APP_DIR)/Resources

SRCS = main.cpp studentas.cpp failo_oper.cpp papild.cpp generavimasf.cpp testai.cpp ListO.cpp DequeO.cpp

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

create_app: all
	mkdir -p $(MACOS_DIR) $(RESOURCES_DIR)
	cp $(TARGET) $(MACOS_DIR)/

	cp generuotasMixas.txt $(RESOURCES_DIR)/
	cp Gstudentai10000.txt $(RESOURCES_DIR)/
	cp Gstudentai100000.txt $(RESOURCES_DIR)/

	# Sukuriam launcher.sh skriptą
	echo '#!/bin/bash' > $(MACOS_DIR)/launcher.sh
	echo 'APP_DIR="$$(dirname "$$0")"' >> $(MACOS_DIR)/launcher.sh
	echo 'exec open -a Terminal "$$APP_DIR/$(TARGET)"' >> $(MACOS_DIR)/launcher.sh
	chmod +x $(MACOS_DIR)/launcher.sh
	chmod +x $(MACOS_DIR)/$(TARGET)

	# Sukuriam Info.plist
	echo '<?xml version="1.0" encoding="UTF-8"?>' > $(APP_DIR)/Info.plist
	echo '<plist version="1.0">' >> $(APP_DIR)/Info.plist
	echo '<dict>' >> $(APP_DIR)/Info.plist
	echo '  <key>CFBundleName</key>' >> $(APP_DIR)/Info.plist
	echo '  <string>Kursiokai</string>' >> $(APP_DIR)/Info.plist
	echo '  <key>CFBundleExecutable</key>' >> $(APP_DIR)/Info.plist
	echo '  <string>launcher.sh</string>' >> $(APP_DIR)/Info.plist
	echo '  <key>CFBundlePackageType</key>' >> $(APP_DIR)/Info.plist
	echo '  <string>APPL</string>' >> $(APP_DIR)/Info.plist
	echo '</dict>' >> $(APP_DIR)/Info.plist
	echo '</plist>' >> $(APP_DIR)/Info.plist

clean:
	rm -f $(TARGET)
	rm -rf $(APP_NAME)
