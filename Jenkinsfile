pipeline {
  agent {
    node {
      label 'lanselot'
    }

  }
  stages {
    stage('build') {
      steps {
        sh '''mkdir -p build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
make -j4
'''
      }
    }

    stage('test') {
      steps {
        sh 'make test'
      }
    }

  }
}