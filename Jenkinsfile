pipeline {
    agent any

    options {
        timestamps() // Add timestamps to logging
        timeout(time: 2, unit: 'HOURS') // Abort pipleine if it runs too long
	
        buildDiscarder(logRotator(numToKeepStr: '8', artifactNumToKeepStr: '8'))
        // disableConcurrentBuilds()
    }

    parameters {
        booleanParam(name: 'RunTestManager', defaultValue: true, description: 'Run all Test Manager tests?')
    }
    
    stages {

        stage('Init') {
            steps {
                echo 'Stage: Init'
                echo "branch=${env.BRANCH_NAME}, RunTestManager=${params.RunTestManager}"
                sh """
                # ssh -V
                # java -version
                # mvn --version
                g++ --version
		# sleep 20  # temp: test build:wait when called from another job
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
        /*
        stage('xxx') {
            steps {
            echo 'Stage: xxx'
                script {
                    timeout(30) {
                        waitUntil {
                            resp = sh "sleep 10", returnStatus: true
                        }
                        return (resp == 0)
                    }
                    if (resp != 0) {
                        build.result = 'ERROR'
                    }
                }
            }
        }
        */
        stage('Test Manager') {
            when {
                expression {
                    // BRANCH_NAME == 'master'
                    params.RunTestManager == true
                }
            }
            //options {
            //    timeout(time: 1, unit: 'MINUTES')
            //}
            steps {
                echo 'Stage: Test'
                echo 'Triggering tm'
                build(job: '/tm/master', propagate: true, wait: true)
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
			cleanWs()
        }
        success {
            echo "post/success"
        }
        failure {
            echo "post/failure"
        }
    }
}
