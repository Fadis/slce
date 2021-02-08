pipeline {
  agent {
    node {
      label 'lanselot'
    }

  }
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