pipeline {
    agent any

    options {
        timestamps() // Add timestamps to logging
        // Abort pipleine if it runs too long
        timeout(time: 2, unit: 'HOURS') 
    }
    
    parameters {
		booleanParam(name: 'RunTestManager', defaultValue: true, description: 'Run all Test Manager tests?')
	}
    
    stages {

        stage('Init') {
            steps {
                echo 'Stage: Init'
                sh """
                ssh -V
                # java -version
                # mvn --version
                g++ --version
                """
            }
        }
        stage('Build') {
            when {
                anyOf {
                    branch 'master'
                    branch 'main'
                }
            }
            steps {
                echo 'Stage: Build'
                sh """
                make clean-all || true
                make
                """
            }
        }
        stage('Test') {
            when {
                expression {
					// BRANCH_NAME == 'master'
					params.RunTestManager == true
				}
            }
            steps {
                echo 'Stage: Test'
                echo 'Triggering tm'
                build(job: '/tm/master', wait: true)
            }
        }
        stage('Cleanup') {
            steps {
                echo 'Stage: Cleanup'
                //deleteDir()
            }
        }

    }
    post {
        always {
            echo "post/always"
            deleteDir() // clean workspace
        }
        success {
            echo "post/success"
        }
        failure {
            echo "post/failure"
        }
    }
}
