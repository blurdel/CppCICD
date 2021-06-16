pipeline {
    agent any

    stages {

        stage('Init') {
            steps {
                echo 'Stage: Init'
            }
        }
        stage('Build') {
            steps {
                echo 'Stage: Build'
                sh 'make'
            }
        }
        stage('Test') {
            steps {
                echo 'Stage: Test'
            }
        }
        stage('Cleanup') {
            steps {
                echo 'Stage: Cleanup'
                deleteDir()
            }
        }

    }
    post {
        success {
            echo "post/success"
        }
        failure {
            echo "post/failure"
        }
    }
}