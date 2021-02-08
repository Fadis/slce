pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        sh '''mkdir -p build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
make -j4
make test'''
      }
    }

  }
}