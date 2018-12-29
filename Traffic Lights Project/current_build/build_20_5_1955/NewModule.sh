#!/bin/bash

PROJ_NAME=$1
PROJ_NAME_U=${PROJ_NAME,,*}
TEMPLATE_DIR=$(find  /media/ -maxdepth 3 -name Templates );
echo "Template directory: $TEMPLATE_DIR";
echo "name: $PROJ_NAME";
echo "name upper: ${PROJ_NAME_U^^}";


mkdir $PROJ_NAME
mkdir $PROJ_NAME/test

cp -i $TEMPLATE_DIR/make/makefile.class $PROJ_NAME/makefile;
chmod +w $PROJ_NAME/makefile;
sed -i s/\|NAME\|/$PROJ_NAME/g $PROJ_NAME/makefile;

cp -i $TEMPLATE_DIR/class/CPP_implementation.cpp $PROJ_NAME/$PROJ_NAME.cpp;
chmod +w $PROJ_NAME/$PROJ_NAME.cpp;
sed -i s/\|NAME\|/$PROJ_NAME/g $PROJ_NAME/$PROJ_NAME.cpp;

cp -i $TEMPLATE_DIR/class/CPP_main.cpp $PROJ_NAME/test/test_$PROJ_NAME.cpp;
chmod +w $PROJ_NAME/test/test_$PROJ_NAME.cpp;
sed -i s/\|NAME\|/$PROJ_NAME/g $PROJ_NAME/test/test_$PROJ_NAME.cpp;

svn add $PROJ_NAME

cp -i $TEMPLATE_DIR/class/CPP_header.h Ainclude/$PROJ_NAME.h;
chmod +w Ainclude/$PROJ_NAME.h;
sed -i s/\|NAME\|/$PROJ_NAME/g Ainclude/$PROJ_NAME.h;
sed -i s/\|GUARD\|/${PROJ_NAME^^}/g Ainclude/$PROJ_NAME.h;
svn add Ainclude/$PROJ_NAME.h
