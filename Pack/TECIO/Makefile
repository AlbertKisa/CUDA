#BOOST_ROOT = /3rdpartylibs/boost/1.59.0/build/linux64-centos6.5/include
BOOST_ROOT = ../
SRCS = arrlist.cpp \
       AsciiOutputInfo.cpp \
       auxdata.cpp \
       checkPercentDone.cpp \
       ClassicFEZoneConnectivityWriter.cpp \
       ClassicFEZoneFaceNeighborGenerator.cpp \
       ClassicFEZoneWriter.cpp \
       ClassicOrderedZoneFaceNeighborGenerator.cpp \
       ClassicOrderedZoneWriter.cpp \
       ClassicZoneFaceNeighborWriter.cpp \
       ClassicZoneHeaderWriter.cpp \
       ClassicZoneVariableWriter.cpp \
       ClassicZoneWriterAbstract.cpp \
       dataio4.cpp \
       dataio.cpp \
       dataset0.cpp \
       dataset.cpp \
       DataSetWriter.cpp \
       datautil.cpp \
       exportSubzonePlt.cpp \
       FaceNeighborGeneratorAbstract.cpp \
       FECellSubzoneCompressor.cpp \
       FieldData.cpp \
       FieldData_s.cpp \
       FileIOStream.cpp \
       FileStreamReader.cpp \
       FileStreamWriter.cpp \
       filestream.cpp \
       FileSystem.cpp \
       fileStuff.cpp \
       geom2.cpp \
       Geom_s.cpp \
       IJKSubzoneInfo.cpp \
       IJKZoneInfo.cpp \
       importSzPltFile.cpp \
       IntervalTree.cpp \
       MinMaxTree.cpp \
       NodeMap.cpp \
       NodeToElemMap_s.cpp \
       ORBFESubzonePartitioner.cpp \
       OrthogonalBisection.cpp \
       PartitionTecUtilDecorator.cpp \
       q_msg.cpp \
       readValueArray.cpp \
       Scanner.cpp \
       set.cpp \
       strlist.cpp \
       strutil.cpp \
       SZLFEPartitionedZoneHeaderWriter.cpp \
       SZLFEPartitionedZoneWriter.cpp \
       SZLFEPartitionWriter.cpp \
       SZLFEZoneHeaderWriter.cpp \
       SZLFEZoneWriter.cpp \
       SZLOrderedPartitionedZoneHeaderWriter.cpp \
       SZLOrderedPartitionedZoneWriter.cpp \
       SZLOrderedPartitionWriter.cpp \
       SZLOrderedZoneHeaderWriter.cpp \
       SZLOrderedZoneWriter.cpp \
       tecio.cpp \
       TecioData.cpp \
       TecioPLT.cpp \
       TecioSZL.cpp \
       TecioTecUtil.cpp \
       TranslatedString.cpp \
       UnicodeStringUtils.cpp \
       writeValueArray.cpp \
       ZoneHeaderWriterAbstract.cpp \
       ZoneInfoCache.cpp \
       Zone_s.cpp \
       ZoneVarMetadata.cpp \
       ZoneWriterAbstract.cpp \
       ZoneWriterFactory.cpp

TECIOLIB = libtecio.a
SZCOMBINE = szcombine
OBJS = $(SRCS:%.cpp=%.o)

CXX = g++
CXXFLAGS = -DLINUX \
		   -DLINUX64 \
		   -DTP_PROJECT_USES_BOOST \
		   -DBOOST_ALL_NO_LIB \
		   -DMAKEARCHIVE \
		   -DNO_THIRD_PARTY_LIBS \
		   -fmessage-length=0 \
		   -fPIC \
		   -isystem \
		   $(BOOST_ROOT) \
		   -fvisibility=hidden  \
		   -w \
		   -O3 \
		   -DNDEBUG \
		   -DNO_ASSERTS
# Add the following for debug builds:
# -g -D_DEBUG \
AR = ar
ARFLAGS = -rc

LDFLAGS = -fPIC -fmessage-length=0 -fvisibility=hidden -Wall

all: $(TECIOLIB) $(SZCOMBINE)

clean:
	rm *.o *.a szcombine

$(OBJS) : %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(TECIOLIB) : $(OBJS)
	$(AR) $(ARFLAGS) $(TECIOLIB) $(OBJS)

$(SZCOMBINE) : szcombine.cpp $(TECIOLIB)
	$(CXX) $< -o $@ $(TECIOLIB) -lpthread
