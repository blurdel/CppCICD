pipeline {
    agent any

    options {
        timestamps() // Add timestamps to logging
        // Abort this pipleine if it runs longer than the timeout
        timeout(time: 2, unit: 'HOURS') 
    }

    tools {
        maven 'mvn'
    }

    stages {

        stage('Init') {
            steps {
                echo 'Stage: Init'
                sh 'ssh -V'
                sh 'java -version'
                sh 'mvn --version'
                sh 'g++ --version'
            }
        }
        stage('Build') {
            when {
                expression {
                    env.BRANCH_NAME == 'master' || env.BRANCH_NAME == 'main'
                }
            }
            steps {
                echo 'Stage: Build'
                // sh 'make'
            }
        }
        stage('Test') {
            steps {
                echo 'Stage: Test'
                build(job: '/tm/master', wait: false)
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
