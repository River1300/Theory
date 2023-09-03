/* ----- < 딥러닝이란? > ----- */

/*
딥러닝은 인공 신경망( artificial neural network )을 기반으로 한 머신러닝의 한 분야
이는 인간의 뇌 신경망을 모방한 구조를 사용하여 데이터에서 의미 있는 패턴을 학습하고 이해하는 데 사용된다. 
딥러닝은 대량의 데이터와 그 데이터에 내재된 복잡한 관계를 이해하고 예측하는 데 특히 유용하며, 
이미지 인식, 음성 인식, 자연어 처리 등 다양한 분야에서 매우 성공적으로 활용되고 있다.

딥러닝은 여러 개의 층( layer )으로 구성된 신경망을 사용하는데, 
이런 구조 때문에 "깊은" 학습을 할 수 있어서 딥러닝이라는 이름이 붙여졌다. 
각 층은 입력 데이터에서 점차적으로 추상적인 특징을 학습하며, 
이러한 층들은 서로 연결되어 복잡한 패턴과 관계를 모델링할 수 있다.

딥러닝의 주요 구성 요소는 다음과 같다.
	입력층( Input Layer )	: 초기 데이터가 들어오는 곳
	은닉층( Hidden Layers )	: 여러 개의 은닉층이 있으며, 데이터의 추상적인 특징을 학습
	출력층( Output Layer )	: 최종 예측이나 분류 결과를 출력
	가중치( Weights )와 편향( Biases )	: 각 층 사이의 연결은 가중치와 편향으로 구성되며, 이들은 학습 과정에서 조절된다.
	활성화 함수( Activation Functions )	: 각 층의 출력을 결정하는 함수로, 비선형성을 추가하여 복잡한 관계를 모델링할 수 있게 해준다.
	역전파( Backpropagation )			: 학습 데이터와 실제 결과 사이의 오차를 줄이기 위해 가중치와 편향을 조절하는 과정

딥러닝은 주로 데이터를 기반으로 자동으로 특징을 학습하므로, 전통적인 방식보다 효과적으로 많은 문제를 해결할 수 있다. 
하지만 많은 데이터와 연산 자원이 필요하며, 모델의 복잡성이 증가할수록 과적합(overfitting) 문제에 주의해야 한다.
*/

/* ----- < Perceptron과 뉴럴 네트워크 > ----- */

/* Perceptron */

/*
딥러닝의 가장 작은 단위 Perceptron

퍼셉트론은 딥러닝의 기본 개념 중 하나로, 간단한 형태의 인공 신경망 구조를 말한다.

고양이와 개를 구분하려고 한다고 해보자.
각 동물의 특징을 살펴보고, 귀의 크기나 코의 형태 등을 관찰하여 이들을 구분하는 방법을 찾고 있다. 
퍼셉트론은 이런 아이디어를 컴퓨터가 이해할 수 있는 방식으로 구현한 것이다.

퍼셉트론은 두 개의 주요 구성 요소로 이루어져 있다. 
하나는 "입력"이고 다른 하나는 "가중치"이다.
	입력( Input ) : 고양이와 개를 구분하기 위해 두 가지 특징을 사용하기로 결정했다고 가정하면
			=> 하나는 "귀의 크기"이고 다른 하나는 "코의 형태"에 대한 정보이다. 
			=> 각각의 특징을 숫자로 표현하자면, 귀의 크기가 0.7이고 코의 형태가 0.5라고 해보자. 이것이 바로 퍼셉트론의 입력이다.
	가중치( Weights ) : 그런데 귀의 크기가 중요한 특징일 수도 있고, 코의 형태가 더 중요한 특징일 수도 있다. 
			=> 이러한 특징의 중요도를 나타내는 숫자를 가중치라고 한다. 
			=> 예를 들어, 귀의 크기가 중요하다고 판단하면 그 가중치를 0.6으로, 
			=> 코의 형태가 더 중요하다고 판단하면 그 가중치를 0.9로 설정해볼 수 있다.

퍼셉트론은 이렇게 입력과 가중치를 곱한 값을 합산하고, 그 결과를 활성화 함수를 통해 변환한다. 
	=> 활성화 함수는 단순히 입력을 더 복잡한 형태로 바꾸어주는 역할도 한다.
마지막으로, 활성화 함수를 거친 결과가 어떤 임계값을 넘으면 퍼셉트론은 출력을 내보낸다. 
	=> 이 출력은 "고양이"일 확률을 나타내는 값이나 "개"일 확률을 나타내는 값일 수 있다.

요약하자면, 퍼셉트론( Perceptron )은 입력과 가중치를 곱하고 활성화 함수를 거쳐서 출력을 생성하는 단순한 구조로, 
이를 통해 간단한 판단을 컴퓨터가 할 수 있게 된다. 이것이 딥러닝의 시작이자 기본 개념이다.
*/

/* Neuron */

/*
뉴런( neuron )은 생물학적 뉴런을 모델로 한 인공 신경망의 기본 단위를 의미한다. 
인공 신경망은 인간의 뇌에서 영감을 받아 만들어진 모델로, 데이터를 처리하고 패턴을 학습하는 데 사용된다. 
인공 뉴런은 생물학적 뉴런의 기본 작동 원리를 모방하여 만들어진 것으로, 
입력을 받아 가중치와 함께 가공하고 활성화 함수를 통해 출력을 생성하는 역할을 수행한다.

인공 뉴런의 구조와 작동 방식
	입력( Input ) : 인공 뉴런은 여러 개의 입력을 받을 수 있다. 
		=> 예를 들어, 이미지 데이터의 경우 각 픽셀의 값을 입력으로 사용할 수 있다.
	가중치( Weights ) : 각 입력에는 가중치가 할당된다. 
		=> 가중치는 해당 입력의 중요도를 나타내는 값으로, 입력과 가중치를 곱한 값들이 뉴런 내에서 계산된다.
	합산( Summation ) : 입력과 가중치를 곱한 값들을 합산하여 하나의 숫자로 만든다. 
		=> 이 합산된 값은 뉴런의 활성화 함수에 입력으로 들어가게 된다.
	활성화 함수( Activation Function ) : 활성화 함수는 합산된 값을 변환하여 출력을 생성한다. 
		=> 이 함수는 비선형성을 추가해 복잡한 패턴을 모델링할 수 있도록 돕는다.
	출력( Output ) : 활성화 함수를 거친 결과가 뉴런의 출력이 된다. 
		=> 이 출력은 다음 뉴런으로 전달되거나 최종 결과를 내놓는 데 사용된다.

딥러닝에서 여러 개의 인공 뉴런을 결합하여 층(layer)을 형성하고, 
이러한 층들을 서로 연결함으로써 복잡한 패턴을 학습하고 데이터를 처리한다. 
이러한 구조를 딥러닝 모델이라고 하며, 이를 통해 이미지, 음성, 텍스트 등 
다양한 데이터에서 유용한 정보를 추출하거나 예측하는 작업을 수행할 수 있다.
*/

/* Neural Network Structure */

/*
딥러닝에서 말하는 "뉴럴 네트워크 구조( neural network structure )"는 인공 뉴런들을 계층적으로 배치하고 
연결하여 데이터 처리 및 학습을 수행하는 모델의 레이아웃과 구성을 의미한다. 
뉴럴 네트워크 구조는 인공 신경망의 구성요소들이 어떻게 배치되고 상호작용하는지를 나타내며, 
데이터의 복잡한 패턴을 이해하고 모델링하는 데 사용된다.

가장 기본적인 뉴럴 네트워크 구조는 "퍼셉트론( perceptron )"으로부터 시작한다. 
하지만 딥러닝에서 사용되는 구조는 이보다 훨씬 더 깊고 복잡한 형태를 가지며, 
다양한 종류의 층과 뉴런이 조합되어 데이터를 처리하고 학습하는 데 사용된다.

일반적으로 딥러닝에서 사용되는 뉴럴 네트워크 구조의 중요한 요소는 다음과 같다.
	입력층( Input Layer ) : 초기 데이터가 들어오는 곳으로, 실제 입력 데이터와 동일한 차원을 가지는 뉴런들로 구성된다.
	은닉층( Hidden Layers ): 하나 이상의 은닉층이 있을 수 있다. 
		=> 은닉층은 입력 데이터의 특징을 추출하고 학습을 위해 중간 단계에서 사용된다.
	출력층( Output Layer ) : 최종 예측이나 분류 결과를 내보내는 곳으로, 원하는 출력 형태에 따라 뉴런들로 구성된다.
	연결( Connectivity ) : 뉴런들 사이의 연결 구조를 나타내는 것이 중요하다. 
		=> 일반적으로 이전 층의 뉴런들이 다음 층의 모든 뉴런과 연결되어 정보가 전달된다.
	가중치( Weights )와 편향( Biases ) : 각 연결에는 가중치와 편향이 할당되며, 이들은 학습 과정에서 조절된다.
	활성화 함수( Activation Functions ) : 뉴런의 출력을 결정하는 함수로, 
		=> 비선형성을 추가하여 네트워크가 복잡한 함수를 모델링할 수 있게 한다.
	깊이( Depth ) : 딥러닝에서 "깊이"는 은닉층의 개수를 나타낸다. 
		=> "깊은( deep )" 학습이라는 용어는 여러 개의 은닉층을 사용하는 것을 의미한다.

뉴럴 네트워크 구조는 다양한 종류로 변형되어 다양한 문제에 적용될 수 있다. 
예를 들어, 컨볼루션 신경망(CNN)은 주로 이미지 처리에 사용되며, 
순환 신경망(RNN)은 순서가 있는 데이터(예: 시퀀스, 시계열)를 처리하는 데 사용된다. 
이러한 구조들을 조합하고 변형함으로써 딥러닝 모델은 다양한 작업에 유연하게 적용될 수 있다.
*/

/* Machine Learning */

/*
머신러닝( Machine Learning )은 컴퓨터 시스템이 데이터로부터 패턴을 학습하고, 
이를 기반으로 결정을 내리거나 예측을 수행하는 인공 지능 분야이다. 
머신러닝은 명시적으로 프로그래밍하지 않고도 컴퓨터가 데이터에서 학습을 통해 지식을 습득하고 
문제를 해결할 수 있는 능력을 갖게 해준다.

머신러닝의 주요 아이디어는 다음과 같다.
	데이터 기반 학습 : 머신러닝은 대량의 데이터를 분석하고, 데이터에 내재된 패턴을 스스로 학습하여 모델을 개발한다. 
		=> 이를 통해 모델은 데이터로부터 추출한 정보를 사용하여 예측, 분류, 클러스터링 등 다양한 작업을 수행할 수 있다.
	자동화된 패턴 발견 : 머신러닝은 컴퓨터가 데이터에서 통계적 패턴이나 의미 있는 정보를 자동으로 발견하도록 돕는다. 
		=> 이를 통해 복잡한 문제를 해결하거나 유용한 통찰력을 얻을 수 있다.
	모델의 일반화 : 머신러닝 모델은 학습 데이터에서 배운 패턴을 새로운 데이터에 일반화하여 적용할 수 있다.
		=> 이는 학습 데이터에 없는 새로운 상황에서도 모델이 유용하게 동작할 수 있음을 의미한다.
	반복적인 학습과 개선 : 머신러닝 모델은 초기에는 일정한 수준의 성능을 보이지만, 
		=> 추가적인 데이터와 반복적인 학습을 통해 점차적으로 성능을 향상시킬 수 있다.

머신러닝은 지능적인 결정과 예측을 자동화하고, 복잡한 문제를 다룰 수 있는 도구로서 널리 활용되며, 
의료, 금융, 이미지 처리, 자연어 처리 등 다양한 분야에서 혁신적인 응용이 이루어지고 있다.
*/

// 2차원 공간에 리니어 클래시파이어로 구분하기 어려운 Data 들이 있다고 가정하면
//	=> 리니어 클래시파이어를 아무리 조합해 보아도 2차원 공간에서는 선 밖에 그릴 수 없다.
//	=> 이를 해결하기 위해 각각의 구분에 non-Linear한 특성을 넣어 주는 것이다.
//		=> 뉴련에 꺼젔다, 켜젔다 하는 함수를 넣어 주어 꺼진 상태와 켜진 상태를 구분 가능하게 해준다.
// tensorflow playground : 뉴럴 네트워크를 가지고 이것저것 실험을 할 수 있는 사이트
//		=> 2차원 공간에 가운데 밀집한 Data 집합 + 그 Data 집합을 감싸는 Data 집합이 있다.
//		=> Activation-Linear 함수를 가지고 클래시파이어를 만든다고 하면 그 모델의 복잡함이랑 상관 없이 구분이 불가능 하다.
//		=> 하지만 각각의 뉴런들에 Activation-ReLU 함수를 넣는다면 하나의 HIDDEN LAYER, 4개의 뉴런 만으로도 구분이 가능하다.

/* ----- < Loss Function, Optimization > ----- */

/*
Loss Function( 손실 함수 ) : 학습된 모델의 출력과 실제 정답( label ) 사이의 차이를 측정하는 함수 
이 함수는 모델이 얼마나 정확하게 작업을 수행하는지를 평가하고, 학습 과정에서 모델의 매개변수( 가중치와 편향 )를 조정하기 위해 사용

손실 함수는 모델의 출력 값과 실제 정답 간의 차이를 계산하는데 사용 
이 차이, 즉 예측 오차를 통해 모델의 성능을 평가하고 학습 과정에서 이 오차를 최소화하려고 한다.
모델이 정확하게 예측하는 경우 손실 함수 값이 작아지며, 예측이 부정확할수록 값이 커진다.

여러 가지 손실 함수가 있으며, 선택하는 손실 함수는 주어진 문제와 모델의 종류에 따라 달라진다. 
일반적인 손실 함수 예시로는 다음과 같은 것들이 있다.
	평균 제곱 오차( Mean Squared Error, MSE ) : 예측 값과 실제 값 간의 차이를 제곱하여 평균화한 값, 회귀 문제에서 주로 사용
	교차 엔트로피 손실( Cross-Entropy Loss ) : 분류 문제에서 주로 사용되며, 
		=> 모델이 예측한 확률 분포와 실제 레이블 간의 차이를 계산
	힌지 손실( Hinge Loss ) : 서포트 벡터 머신( Support Vector Machine )과 같은 모델에서 사용되며, 
		=> 분류 문제에서 경계면을 찾는데 사용
	사용자 정의 손실 함수 : 특정 문제에 맞게 사용자가 직접 정의한 손실 함수를 사용할 수도 있다. 
		=> 예를 들어, 특정 비즈니스 목표를 반영하기 위해 손실 함수를 설계할 수 있다.

손실 함수의 값은 학습 중에 최소화되도록 모델의 매개변수를 조정하는 데 사용된다. 
이러한 과정은 주로 "경사 하강법( Gradient Descent )"과 같은 최적화 알고리즘을 통해 이루어진다. 
손실 함수를 최소화하는 방향으로 모델의 매개변수를 조정하면, 모델이 더 나은 예측을 수행할 수 있도록 학습된다.
*/

/*
Optimization( 최적화 ) : 모델의 매개변수를 조정하여 손실 함수를 최소화하거나 최대화하는 과정을 말한다. 
최적화는 모델을 훈련시키는 핵심 단계 중 하나로, 모델의 예측 성능을 향상시키기 위해 가중치와 편향 같은 
매개변수를 조정하는 방법을 포함한다.

기본적으로 최적화는 다음과 같은 핵심 개념으로 이루어져있다.
	손실 함수 ( Loss Function ) : 최적화의 목표는 손실 함수를 최소화하는 것 
		=> 손실 함수는 모델의 출력과 실제 정답 사이의 차이를 측정
		=> 최적화 과정에서는 이 손실 함수 값을 줄이기 위해 모델의 매개변수를 조정
	경사 하강법 ( Gradient Descent ) : 경사 하강법은 최적화 알고리즘 중 하나로, 4
		=> 손실 함수의 그래디언트( 기울기 )를 이용하여 모델의 매개변수를 조정
		=> 그래디언트는 손실 함수 값이 가장 크게 증가하는 방향을 가리키는데, 
		=> 경사 하강법은 그래디언트 반대 방향으로 매개변수를 업데이트하여 손실 함수 값을 감소시킨다.
	학습률 ( Learning Rate ) : 경사 하강법에서는 학습률이라는 하이퍼파라미터를 사용
		=> 학습률은 한 번의 업데이트 단계에서 얼마나 크게 매개변수를 조정할지 결정하는 요소이다. 
		=> 적절한 학습률을 선택하는 것이 중요
		=> 너무 작으면 최적화가 느려질 수 있고, 너무 크면 최적점을 지나칠 수 있다.
	배치 크기 ( Batch Size ) : 학습 데이터를 한 번에 모두 사용하는 것이 아니라, 
		=> 작은 배치로 나누어 각 배치마다 모델의 매개변수를 업데이트한다.
		=> 이는 계산 효율성과 최적화 과정의 안정성을 균형있게 유지하기 위한 전략입니다.
	에포크 ( Epoch ) : 학습 데이터를 전체로 사용하여 한 번의 최적화 과정을 완료하는 것을 에포크라고 한다. 
		=> 보통 여러 에포크를 거쳐 모델을 훈련하며, 에포크마다 손실 함수 값이 줄어들도록 매개변수를 조정

딥러닝에서는 경사 하강법을 비롯한 다양한 최적화 알고리즘이 개발되어 있으며, 
모델과 문제에 따라서 적절한 최적화 알고리즘과 하이퍼파라미터를 선택하여 모델을 효과적으로 학습시킬 수 있다.
*/

/* ----- < Backpropagation > ----- */

/*
Backpropagation( 역전파 ) : 인공 신경망의 학습 과정에서 사용되는 알고리즘, 
손실 함수의 값을 최소화하기 위해 모델의 매개변수를 조정하는 방법 
역전파는 신경망의 각 층에 대한 그래디언트(기울기)를 계산하고, 
이를 사용하여 경사 하강법과 같은 최적화 알고리즘을 적용하여 모델을 학습시킨다.

역전파 단계
	순전파( Forward Propagation ) : 입력 데이터가 모델을 통과하며, 각 층의 활성화 값을 계산한다. 
		=> 이 활성화 값들은 다음 층으로 전달되며, 최종 출력을 생성
	손실 함수 계산( Loss Calculation ) : 모델의 예측 결과와 실제 정답( label )을 비교하여 손실 함수의 값을 계산한다. 
		=> 이 손실 함수는 모델의 성능을 평가하는데 사용된다.
	역전파( Backpropagation ) : 역전파 단계에서는 손실 함수의 그래디언트를 계산한다. 
		=> 그래디언트는 각 매개변수의 변화에 따른 손실 함수의 변화를 나타내며, 
		=> 각 층에서 그래디언트를 계산하여 이전 층으로 전달
	매개변수 업데이트( Parameter Update ) : 각 층에서 계산된 그래디언트를 사용하여 경사 하강법과 같은 
		=> 최적화 알고리즘을 통해 모델의 매개변수( 가중치와 편향 )를 업데이트한다.
		=> 이 과정을 통해 손실 함수 값을 최소화하거나 최대화하는 방향으로 모델이 조정된다.
	반복( Iteration ) : 위의 단계를 여러 번 반복하여 모델을 계속 학습시킨다. 
		=> 각 에포크( epoch )마다 데이터를 사용하여 순전파와 역전파를 수행하고 매개변수를 업데이트한다. 
		=> 이 과정을 충분한 횟수만큼 반복하면 모델이 원하는 수준의 성능을 얻을 수 있게 된다.

역전파 알고리즘은 딥러닝의 핵심이며, 모델의 매개변수를 효과적으로 학습시키는 데 사용된다. 
이 과정을 통해 모델은 입력과 출력 간의 복잡한 관계를 학습하고, 데이터로부터 패턴을 추출하여 다양한 작업을 수행할 수 있게 된다.
*/

/* ----- < Batch Learning > ----- */

/*
배치 학습( Batch Learning ) : 모델이 학습 데이터를 작은 배치로 나누어 각 배치마다 모델의 매개변수를 업데이트하는 학습 방법을 말한다. 
							=> 배치 학습은 전체 학습 데이터를 한 번에 사용하는 전통적인 방법과 대조적인 방식이다.

배치 학습 특징 : 
	데이터 배치 : 전체 학습 데이터를 작은 크기의 배치로 나누어 모델을 학습시킨다. 
				=> 각 배치는 입력 데이터와 그에 해당하는 정답( label )으로 구성된다.
	그래디언트 계산 : 각 배치에 대해 순전파와 역전파를 수행하여 손실 함수의 그래디언트( 기울기 )를 계산 
					=> 이 그래디언트는 배치 내의 데이터를 기반으로 모델의 매개변수를 업데이트하는 데 사용된다.
	매개변수 업데이트 : 각 배치에서 계산된 그래디언트를 사용하여 모델의 매개변수를 업데이트한다. 
					=> 이 업데이트는 경사 하강법과 같은 최적화 알고리즘을 통해 이루어진다.

배치 학습은 큰 데이터셋을 다룰 때 유용한 장점을 가지고 있다.
	계산 효율성 : 전체 데이터를 한 번에 사용하는 것보다 작은 배치로 나눠 학습하는 방식은 계산이 더 효율적이다. 
				=> 특히 GPU와 같은 병렬 처리 장치를 활용할 때 이점이 크다.
	메모리 효율성 : 전체 데이터를 메모리에 한꺼번에 로드하지 않아도 되므로 메모리 사용량을 줄일 수 있다.
	변동성 감소 : 배치 학습은 각 배치마다 업데이트를 수행하므로 손실 함수 값의 변동성이 낮아져 모델의 안정성을 높일 수 있다.

하지만 배치 학습은 몇 가지 단점도 가지고 있다.
	수렴 속도 : 한 번에 많은 데이터를 사용하는 전체 데이터 학습 방식에 비해 수렴 속도가 느릴 수 있다.
	지역 최소값 : 배치별로 업데이트를 수행하다보면 지역 최소값에 빠져 더 나은 전역 최소값을 찾는 데 어려움이 있을 수 있다.

따라서 배치 크기를 적절히 선택하는 것이 중요하며, 작은 배치 크기는 노이즈로 인한 영향을 줄이고 더 빠른 학습을 할 수 있게 할 수 있다.
*/