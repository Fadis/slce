pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        sh 'make -j4'
      }
    }

    stage('test') {
      steps {
        sh 'make test'
      }
    }

  }
}