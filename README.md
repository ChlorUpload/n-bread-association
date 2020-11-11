# n-bread-association
An application helps DGIST members buy bundled product together.

## purpose
When shopping online, bundled products are usually less expensive than those sold in
individual pieces. However, since it is not common for students to use or eat one thing that much,
DGIST members should pay more to buy less stuff. N빵협회 is an app to solve this problem. On this
app, DGIST members can see the list of products that other members registered. If one could not find
items they want, they can register a new one. In this case, the student is called the host. When they
find one, the user can enroll their name to the list to indicate that they want to buy that product. After
a sufficient number of members are enrolled, the host and the registered members can order the stuff
online.

## project

### 1. n-bread-association-exercise
프로젝트 `n-bread-association-exercise` 는 OOP 원정대원의 C++ 실력을 기르기 위해 진행한 모의 팀프로젝트로 단항식과 다항식을 간단하게 구현했습니다.

### 2. n-bread-association-server-exercise
프로젝트 `n-bread-association-server-exercise` 는 Boost Beast 를 이용한 Asynchronous, Multithread 를 지원하는 웹 서버를 만들고 연습하기 위해서 만들어진 프로젝트입니다.


## timeline

2020-10-26. 아이디어 회의  
2020-10-27. 애플리케이션 디자인 초안 및 Proposal 작성  
2020-11-01. Github repository 생성 및 test project 실습  
2020-11-03. 테스트 서버 작성, Git 활용법 및 C++ 실습 진행  
2020-11-08. 세부사항 기획, 디자인 개선, 데이터베이스 설계 작업 진행

## design

현재까지 만들어진 N빵협회 디자인을 [여기](https://xd.adobe.com/view/88d84aee-b64a-44ee-b642-7646100e6126-dd8b/) 에서 확인 해 보실 수 있습니다.

## CQRS

ViewModels

| Name               | Descrpition                                                  |
| ------------------ | ------------------------------------------------------------ |
| ProductView        | 상품의 미리보기 정보(카테고리, 만료일, 제목, 개당  가격, 현재 모집 개수, 전체 모집 개수, optional: 내 멤버 상태)를 담는 클래스 |
| Enum MemberType    | 상품에 대한 멤버 유형을 나타내는 열거형. public, nonhost, host 가 있음 |
| ProfileView        | 유저(자신)의 프로필 정보(유저id, 유저  이름, 이메일, 인증 여부)를 담는 클래스 |
| ProductDetailView  | 상품의 세부 정보(ProductView를  Composite하고 제품 상세 링크, 공지사항)을 담는 클래스 |
| Enum DeliveryState | 배송 상태를 나타내는 열거형.  preparing, on_deliver, finished 가 있음 |
| ProductNonhostView | ProductDetailView를 Composite하고 현재  참여 인원, 입금 인원, 나의 입금 상태, 내가 구매한 개수, 배송 상태,  커뮤니티 링크를 추가적으로 담는 클래스 |
| ProductHostView    | ProductDetailView를 Composite하고 배송  상태, MemberDetail의 배열을 담는 클래스 |
| UserView           | 유저의 정보(유저id, 유저 이름)                               |
| MemberDetail       | 상품 구매에 참여하는 멤버의 UserView,  구매 수량, 입금 상태를 담는 클래스 |

 

Public Queries

| Name              | Parameters | Return            | Description                                             |
| ----------------- | ---------- | ----------------- | ------------------------------------------------------- |
| PublicGetProducts | Category[] | ProductView[]     | 주어진 카테고리에 속하는 상품 목록을 가져옵니다.        |
| GetCategories     | N/A        | Category[]        | 카테고리 목록을 가져옵니다.                             |
| SearchProducts    | string     | ProductView[]     | 주어진 문자열을 제목에 포함하는 상품 목록을 가져옵니다. |
| GetProductDetail  | productId  | ProductDetailView | 주어진 id의 상품의 세부  정보를 가져옵니다.             |

 

Restricted Queries

| Name              | Parameters                                 | Return             | Description                                                  |
| ----------------- | ------------------------------------------ | ------------------ | ------------------------------------------------------------ |
| GetProducts       | AccessToken,  Category[],  Enum MemberType | ProductView[]      | 멤버 유형에 따라 주어진 카테고리에 속하는 상품 목록을 가져옵니다. PublicGetProducts은 멤버 상태를 public으로만  반환하는 것과 달리 나의 멤버 상태를 추가적으로 받아올 수 있습니다. |
| GetProfile        | AccessToken                                | ProfileView        | 내 프로필 정보를 가져옵니다.                                 |
| GetProductNonhost | AccessToken  ProductId                     | ProductNonhostView | Nonhost멤버에게 필요한 상품 상세 정보를 가져옵니다. Nonhost가 아닌 유저가 요청하면 Privilege Exception을  throw합니다. |
| GetProductHost    | AccessToken  ProductId                     | ProductHostView    | Host멤버에게 필요한 상품 상세 정보를 가져옵니다.  Host가 아닌 유저가 요청하면 Privilege  Exception을 throw합니다. |
| GetMemberType     | AccessToken  ProductId                     | Enum MemberType    | 나의 멤버 상태를 받아옵니다.                                 |

 

Commands

| Name             | Parameters                                 | Return        | Description                                                  |
| ---------------- | ------------------------------------------ | ------------- | ------------------------------------------------------------ |
| CancelMembership | AccessToken                                | bool          | 회원을 탈퇴하고 성공 여부를 반환합니다.                      |
| SetDepositState  | AccessToken  userId  productId  bool       | bool          | 유저의 입금 상태를 변경하고 성공 여부를 반환합니다. 내가 Host가 아닐 경우에는 Privilege Exception을 throw합니다. User가 Product의 Member가  아닐 경우에는 Invalid access Exception을 throw합니니다. |
| SetDeliveryState | AccessToken  ProductId  Enum DeliveryState | bool          | 상품의 배송 상태를 변경하고 성공 여부를 반환합니다. 내가 Host가 아닐 경우에는 Privilege Exception을 throw합니다. |
| SetAnnounce      | AccessToken  ProductId  string             | bool          | 상품의 공지사항을 변경하고 성공 여부를 반환합니다. 내가 Host가 아닐 경우에는 Privilege Exception을 throw합니다. |
| RegisterProduct  | AccessToken  Product                       | Int ProductId | 상품 등록 정보를 받아 상품을 등록합니다. 상품 등록 후 ProductId를 반환합니다. 만약 등록이 실패한다면 -1을 반환합니다. |

 

