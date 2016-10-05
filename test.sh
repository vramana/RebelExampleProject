#!/bin/sh
set -x

if [ $BUCKLESCRIPT = true ]; then
  cd bucklescript-backend && npm i -S bloomberg/bucklescript#make_bsc_not_affect_by_OCAMLLIB && npm i && npm test
else
  cd native-backend && npm i && npm test
fi
