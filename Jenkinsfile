pipeline {
  agent {
    node {
      label 'lanselot'
    }

  }
  stages {
    stage('build') {
      steps {
        ansiColor(colorMapName: 'gnome-terminal') {
          sh '''mkdir -p build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr
make -j4
make test'''
        }

      }
    }

  }
}