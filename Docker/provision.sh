#!/bin/bash

# Update Package List
apt-get update
apt-get upgrade -y

#Install utilities
apt-get install -y g++ curl git

#Download MNIST training data
curl http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz --output train-images.gz
curl http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz --output train-labels.gz
curl http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz --output test-images.gz
curl http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz --output test-labels.gz

#Unzip
gunzip train-images.gz
gunzip train-labels.gz
gunzip test-images.gz
gunzip test-labels.gz

#Download source 
git clone https://github.com/Vafilor/AdventuresInCpp.git

#Compile C++ programs
cd AdventuresInCpp
cd Matrix
g++ -std=c++14 -O2 Matrix.cpp -c -o matrix.o
cd ../NeuralNetwork
g++ -std=c++14 -O2 DataInputTester.cpp NeuralNetwork.cpp HandWritingDataInput.cpp Timer.cpp  -I../Matrix ../Matrix/matrix.o -o /train.out





