pipeline {
    agent any

    stages {

        stage('Init') {
            steps {
                echo 'Stage: '
            }
        }
        stage('Build') {
            steps {
                echo 'Stage: Build'
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