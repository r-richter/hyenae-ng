#
# Hyenae NG
#   Advanced Network Packet Generator (NextGen)
#
# Copyright (C) 2020 Robin Richter
#
#   Contact  : richterr@users.sourceforge.net
#   Homepage : https://github.com/r-richter/hyenae-ng
#
# This file is part of Hyenae NG.
#
# Hyenae NG is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Hyenae NG is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Hyenae NG.  If not, see <http://www.gnu.org/licenses/>.
#

APP = hyenae-ng
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

ifeq ($(OS),Windows_NT)
	LIBS=-l wpcap
else
	LIBS=-l pcap -l pthread
endif

all :\
	common.o\
	model.o\
	model_data_transformations.o\
	model_generators.o\
	model_generators_protocols.o\
	model_outputs.o\
	console_io.o\
	console_states.o\
	console.o
	$(CXX) $(CXXFLAGS) -o $(APP) ./*.o $(LIBS)

common.o:
	$(CXX) $(CXXFLAGS) -c ./src/*.cpp

model.o:
	$(CXX) $(CXXFLAGS) -c ./src/model/*.cpp

model_data_transformations.o:
	$(CXX) $(CXXFLAGS) -c ./src/model/data_transformations/*.cpp

model_generators.o:
	$(CXX) $(CXXFLAGS) -c ./src/model/generators/*.cpp

model_generators_protocols.o:
	$(CXX) $(CXXFLAGS) -c ./src/model/generators/protocols/*.cpp

model_outputs.o:
	$(CXX) $(CXXFLAGS) -c ./src/model/outputs/*.cpp

console_io.o:
	$(CXX) $(CXXFLAGS) -c ./src/frontend/console/io/*.cpp

console_states.o:
	$(CXX) $(CXXFLAGS) -c ./src/frontend/console/states/*.cpp

console.o:
	$(CXX) $(CXXFLAGS) -c ./src/frontend/console/*.cpp

clean:
	rm -f *.o $(APP) $(APP).exe
