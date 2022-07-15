/// The Alexander Duality (31636 & 31628)- нищо че той не е писал практикума(трябва да си дам кредит)
#include <iostream>
#include <random>
#include <queue>
#include <list>
#include <fstream>

using namespace std;


enum class Subject { analysis, algebra, sdp, custom }; /// само 4 възможни предмета
enum class TeacherType { lecturer, ta};             ///лектор и асистент
enum class ChasType { work, bbreak, sbreak, dupka };/// час , голямо междучасие, малко , дупка
ofstream myfile;    ///директно прави файл при пускането на програмата(пази го в папката, в която се пуска програмата)

class Hero
{
    public:
        string Name = "Az";
        int Failures=3;
        double HealthPoints=150;
        double MentalPoints=10;
        double DumbQuestion=20;
        list <string> Inventory = {"Soleti","Soleti","Pillow","Book","Piko"};
};

class Teacher
{
    public:
        Subject subject;
        TeacherType type;
        int TeachingSkills;
        double Bonuses[3];
};

struct chas
{
    ChasType type;///вид на часа
    Teacher teacher;///кой го преподава
};

void Failure(queue<chas> &day, Hero &Student) {  ///ако студента умре
    Student.Failures--;

    if(Student.Failures <= 0) {
        cout<< "|----------- GAME OVER ----------|"<<endl;
        cout<<"FMI HAS EATEN YOU ALIVE, GAME OVER!!!!!"<<endl;
        myfile<< "|----------- GAME OVER ----------|"<<endl;
        myfile<<"FMI HAS EATEN YOU ALIVE, GAME OVER!!!!!"<<endl;
        exit(1);
    }

    while (!day.empty())///да попне всичко, останалия ден в който е умрял
    {
        day.pop();
    }

    Student.HealthPoints = 90;///60% от 150 кръв
    cout<< "YOU CANNOT GO ON AND RETURN HOME TO REST"<<endl;
    myfile<< "YOU CANNOT GO ON AND RETURN HOME TO REST"<<endl;
}

double RandomNum(int lower, int upper) ///генерира произволни числа
{
    double num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

string print_enum(ChasType type) {    ///принтира видът на блока(час,дупка,т.н)
    string str ="none";
    switch(type) {
        case ChasType::work : return str ="work";
        case ChasType::bbreak : return str ="bbreak";
        case ChasType::sbreak : return str ="sbreak";
        case ChasType::dupka : return str ="dupka";
    }
    return str;
}

string print_chas_type(Subject type) {///принтира предмета
    string str ="none";
    switch(type) {
        case Subject::analysis : return str ="analysis";
        case Subject::algebra : return str ="algebra";
        case Subject::sdp : return str ="sdp";
        case Subject::custom : return str ="custom";
    }
    return str;
}

void PrintProgram(queue<chas> day) { ///принтира програмата за деня
    int i=1;
    cout<<"Daily program:\n";
    myfile<<"Daily program:\n";
    while (!day.empty())
    {

        if(day.front().type == ChasType::dupka) {       ///ако е дупка
            cout<<"dupka"<< '\n';
            myfile<<"dupka"<< '\n';
            day.pop();
            continue;
        }
        else if(day.front().type != ChasType::work) {   ///или ако е редовен час
            day.pop();
            continue;
        }
        cout<<print_chas_type(day.front().teacher.subject) << '\n';      ///принти дължината и предмета
        myfile<<print_chas_type(day.front().teacher.subject) << '\n';
        day.pop();
        i++;
    }
    cout<<"\n";
    myfile<<"\n";
}
string print_teacher_type(TeacherType type) {           ///лектора има лекции / асистента има упражнение(знам че е нахакано ама голям праз)
    string str ="none";
    switch(type) {
        case TeacherType::lecturer : return str ="lecture";
        case TeacherType::ta : return str ="exercise";
    }
    return str;
}
/// ПОЛЗВАНЕ НА ДЕЙСТВИЯ
// 1 Action
void use_inventory(Hero &Student) {
    if(Student.Inventory.empty())                   ///при празен инвентар да медитира(предпочетохме ако имаш предмети да ги ползваш
    {                                               /// а не да избираш между предмет/медитация, защото предмета винаги дава повече
        cout<<"No items so we meditate"<<endl;      ///статове от медитацията
        myfile<<"No items so we meditate"<<endl;
        cout<<"Meditate-> +5hp"<<endl;
        myfile<<"Meditate-> +5hp"<<endl;
        Student.HealthPoints+=5;
    }
    else if(!Student.Inventory.empty())         ///ако има нещо в инвентара, да те пита какво искаш
    {
        cout<<"Choose item: \n";
        myfile<<"Choose item: \n";
        list<string>::iterator ptr;
        int i=1;
        for (ptr = Student.Inventory.begin(); ptr != Student.Inventory.end(); ptr++){   ///обхожда целия лист и ти принти itemите
            cout << "Item: "<< i << ") " << *ptr << "\n";
            i++;
        }
        int temp;
       list<string>::iterator it = Student.Inventory.begin();
        cin>>temp;                                                  ///тук вече потребителя избира какво иска
        advance(it, temp-1);    ///std::advance приема стартова и крайна позиция. Пример при advance(it,5) отива на 6тия елем. Вместо цял цикъл само за това
        if(*it=="Soleti") {
            cout<<"Soleti-> +9hp"<<endl;
            myfile<<"Soleti-> +9hp"<<endl;
            Student.HealthPoints+=9;
        }
        else if(*it=="Book") {
            cout<<"Book-> +10mp"<<endl;                         /// mp са ментални dp са за тъп въпрос
            myfile<<"Soleti-> +10mp"<<endl;
            Student.MentalPoints+=10;
        }
        else if(*it=="Pillow") {
            cout<<"Pillow-> +10hp"<<endl;
            myfile<<"Pillow-> +10hp"<<endl;
            cout<<"Pillow-> +10dp"<<endl;
            myfile<<"Pillow-> +5dp"<<endl;
            Student.HealthPoints+=10;
            Student.DumbQuestion+=5;
        }
        else if(*it=="Piko") {                              ///пикото е предимно за тестове, щото по условие трудно се оцелява повече от 2/3 часа(беше супер ОП(счупи програмата))
            cout<<"Piko -> +10hp"<<endl;
            myfile<<"Piko -> +100hp"<<endl;
            cout<<"Piko -> +5mp"<<endl;
            myfile<<"Piko -> +5mp"<<endl;
            cout<<"Piko-> +5dp"<<endl;
            myfile<<"Piko -> +5dp"<<endl;
            Student.HealthPoints+=10;
            Student.DumbQuestion+=5;
            Student.MentalPoints+=5;
        }
        else {                                              ///ако потребителя получи инфаркт
            cout<<"Not a valid option, dumbass, you wasted a point"<<endl;
            myfile<<"Not a valid option, dumbass, you wasted a point"<<endl;
        }
        Student.Inventory.erase(it);                ///след използването на предмет, да го маха
    }
}
// 2 Actions

void lafka(Hero &Student) {                     ///тук вече за 2 действия
    int temp ;
    cout<<"You fumble down the stairs, seeking sustinance"<<endl<<"but having gotten down there, are caught in a trilemma as to what to buy\n";
    cout<<"Type 1) for vafla |  Type 2) for slushane | Type 3) for 3pak soleti "<<endl;
    myfile<<"You fumble down the stairs, seeking sustinance"<<endl<<"but having gotten down there, are caught in a trilemma as to what to buy\n";
    myfile<<"Type 1) for vafla |  Type 2) for slushane | Type 3) for 3pak soleti "<<endl;
    cin>>temp;
    if(temp==1)                                                     ///аналогично си избираш какво искаш и то го прави
    {
        cout<<" Vafla-> +15hp"<<endl;
        myfile<<" Vafla-> +15hp"<<endl;
        Student.HealthPoints+=15;
    }
    else if(temp==2)
    {
        cout<<"slushame razgovor -> dumb question +1.5"<<endl;
        myfile<<"slushame razgovor -> dumb question +1.5"<<endl;
        Student.DumbQuestion+=1.5;
    }
    else  if(temp==3)
    {
        cout<<" zapasqvane sus 3pak soleti + 9hp"<<endl;
        myfile<<" zapasqvane sus 3pak soleti + 9hp"<<endl;
        for(int i=0; i<3; i++)
            Student.Inventory.push_front("Soleti");

        Student.HealthPoints+=9;
    }
    else
    {
        cout<<" you havent chosen a valid options "<<endl;
        myfile<<" you havent chosen a valid options "<<endl;
        exit(1);
    }
}

// 3 Actions
void fifth_floor(Hero &Student) {                   /// за 3 действия
    int temp;
    cout<<"You take the daunting trek towards the elusive fifth floor,"<<endl<<"and having gotten there, wonder what to do\n";
    cout<<"Type 1) for spane or 2) for uchene "<<endl;
    myfile<<"You take the daunting trek towards the elusive fifth floor,"<<endl<<"and having gotten there, wonder what to do\n";
    myfile<<"Type 1) for spane or 2) for uchene "<<endl;
    cin>>temp;                                      ///аналогично, потребителя си избира какво иска
    if(temp==1)
    {
        cout<<" spane -> +20hp "<<endl;
        myfile<<" spane -> +20hp "<<endl;
        Student.HealthPoints+= 20;
    }
    else if(temp == 2)
    {
        cout<<"Uchene -> +4 mental  +0.5 dumb question"<<endl;
        myfile<<"Uchene -> +4 mental  +0.5 dumb question"<<endl;
        Student.MentalPoints+=4;
        Student.DumbQuestion+=0.5;
    }
    else
    {
        cout<<"Better chose something valid next time -> -1 mental";                ///адаша го предложи
        myfile<<"Better chose something valid next time -> -1 mental";
        Student.MentalPoints-=1;
    }
}


void actions(int Actions,Hero &Student)                 /// Тук вече е цялостната функция за действията, като вика 3те по малки (да не става претруфено)
{
    int temp ;
    while(Actions > 0) {
        cout<<"\nYou currently have " << Actions << " actions, choose wisely\n";
        cout<<"Type 1) for inventory - 1 action \nType 2) for lafka - 2 actions \nType 3) to go the the third floor - 3 actions"<<endl;
        myfile<<"\nYou currently have " << Actions << " actions, choose wisely\n";
        myfile<<"Type 1) for inventory - 1 action \nType 2) for lafka - 2 actions \nType 3) to go the the third floor - 3 actions"<<endl;
        cin>>temp;
        if(temp>Actions) {                                                              ///ако потребителя иска да прави нещо за повече действия отколкото има
            cout<<"Not enough Action points! Try again\n";
            myfile<<"Not enough Action points! Try again\n";
            continue;
        }
        if(temp==1)
        {
            use_inventory(Student);
            Actions-=1;
        }
        else if(temp==2)
        {
            lafka(Student);
            Actions-=2;
        }
        else  if(temp==3)
        {
            fifth_floor(Student);
            Actions-=3;
        }
        else
        {
            cout<<"You have chosen to be useless, congratulations!\n";
            myfile<<"You have chosen to be useless, congratulations!\n";
            break;
        }
    }
}

Teacher EnterTeacher(Subject subject, TeacherType type)                     ///тази функция просто присвоява на всички учители техните данни(доста хардкодване от условието)
{
    Teacher temp;
    temp.subject=subject;
    temp.type=type;

    if(subject==Subject::algebra)
    {
        if(type==TeacherType::lecturer)
        {
            temp.TeachingSkills=29;
            temp.Bonuses[0]=2;  ///бонус психическа сила
            temp.Bonuses[1]=3;  ///бонус живот
            temp.Bonuses[2]=0.1;///въпроси
        }
        else
        {
            temp.TeachingSkills=21;
            temp.Bonuses[0]=1;  ///бонус психическа сила
            temp.Bonuses[1]=5;  ///бонус живот
            temp.Bonuses[2]=0.05;///въпроси
        }
    }

    if(subject==Subject::analysis)
    {
        if(type==TeacherType::lecturer)
        {
            temp.TeachingSkills=23;
            temp.Bonuses[0]=2;  ///бонус психическа сила
            temp.Bonuses[1]=4;  ///бонус живот
            temp.Bonuses[2]=0.2;///въпроси
        }
        else
        {
            temp.TeachingSkills=21;
            temp.Bonuses[0]=1;  ///бонус психическа сила
            temp.Bonuses[1]=5;  ///бонус живот
            temp.Bonuses[2]=0.05;///въпроси
        }
    }
    if(subject==Subject::sdp)
    {
        if(type==TeacherType::lecturer)
        {
            temp.TeachingSkills=29;
            temp.Bonuses[0]=2;  ///бонус психическа сила
            temp.Bonuses[1]=3;  ///бонус живот
            temp.Bonuses[2]=0.1;///въпроси
        }
        else
        {
            temp.TeachingSkills=21;
            temp.Bonuses[0]=1;  ///бонус психическа сила
            temp.Bonuses[1]=5;  ///бонус живот
            temp.Bonuses[2]=0.05;///въпроси
        }
    }

    if(subject==Subject::custom)                                    ///никъде по условие не си ни искал други предмети, но добавих един custom че програмата да не е еднообразна
    {
        if(type==TeacherType::lecturer)
        {
            temp.TeachingSkills=20;
            temp.Bonuses[0]=1;  ///бонус психическа сила
            temp.Bonuses[1]=3;  ///бонус живот
            temp.Bonuses[2]=0.1;///въпроси
        }
        else
        {
            temp.TeachingSkills=15;
            temp.Bonuses[0]=1;  ///бонус психическа сила
            temp.Bonuses[1]=4;  ///бонус живот
            temp.Bonuses[2]=0.05;///въпроси
        }
    }

    return temp;
}

void work(queue <chas> &day, chas hour, Hero &Student, Teacher *Sustav) {                                   /// ПРОЦЕС НА ЛЕКЦИЯТА
    double TotalDamage=0;

    cout << "Starting "<< print_chas_type(hour.teacher.subject) << " classes - " << print_teacher_type(hour.teacher.type) << "\n\n";        /// принти какъв предмет е в момента
    myfile << "Starting "<< print_chas_type(hour.teacher.subject) << " classes - " << print_teacher_type(hour.teacher.type) << "\n\n";

    if( hour.teacher.type == TeacherType::lecturer){                            /// ДМГ на лектор
        TotalDamage = (RandomNum(80,100)/100)*hour.teacher.TeachingSkills - (RandomNum(40,100)/100)*Student.MentalPoints;
    }

    if( hour.teacher.type == TeacherType::ta){                                  ///ДМГ  на асистент
        TotalDamage = (RandomNum(60,100)/100)*hour.teacher.TeachingSkills - (RandomNum(40,100)/100)*Student.MentalPoints;
    }

    for(int i=0; i<4; i++)                                              ///4те рунда на 1 час лекция
    {
        if(rand() % 100 < Student.DumbQuestion){                        ///шанса за тъп въпрос
            cout<<"Dumb question hits critical confusion -> 25% less damage "<<endl;
            myfile<<"Dumb question hits critical confusion -> 25% less damage "<<endl;
            TotalDamage *= 0.75;                                        /// намаляването на ДМГ
        }
        if(TotalDamage<=0){                                             ///ако имаме късмет с генерирането да не бие отрицателен ДМГ
            cout<<"The Teacher is too weak to deal damage, the rest of the lecture went smoothly"<<endl;
            myfile<<"The Teacher is too weak to deal damage, the rest of the lecture went smoothly"<<endl;
            break;
        }
        cout<<"Teacher dealt "<< TotalDamage <<" damage"<<endl;             ///после принтим колко е набил
        myfile<<"Teacher dealt "<< TotalDamage <<" damage"<<endl;
        Student.HealthPoints-=TotalDamage;                                  ///намаляваме кръвта на студента
        cout<<"Student's current hp is "<<Student.HealthPoints<<endl;
        cout<<"\n";
        myfile<<"Student's current hp is "<<Student.HealthPoints<<endl;     ///и я принтим колко е след удара
        myfile<<"\n";
        if(Student.HealthPoints<=0){///ако умре, да вика функ за умиране
            Failure(day, Student);
            break;
        }
    }
    cout<<"Classes have ended "<<endl;                                      ///и най-накрая да приключва деня
    myfile<<"Classes have ended "<<endl;
}

void LectureProcess(queue <chas> &day,Hero &Student, Teacher *Sustav)   /// както с функ с действията, пак така викаме помощните, за да пише кога е час/дупка/т.н
{                                                                       /// знам че има тъпо име, ти измисли по-добро
    while(!day.empty())
    {
        chas hour = day.front();
        day.pop();
        if(hour.type == ChasType::work) {
            work(day, hour, Student, Sustav);
        }
        if(hour.type == ChasType::dupka) {
            cout<<"GOD HAS FORSAKEN YOU IN THIS DUPKA\n"<<endl;
            myfile<<"GOD HAS FORSAKEN YOU IN THIS DUPKA\n"<<endl;
            actions(4, Student);
        }
        if(hour.type == ChasType::bbreak) {
            cout<<"Big mamma break\n"<<endl;
            myfile<<"Big mamma break\n"<<endl;
            actions(2, Student);
        }
        if(hour.type == ChasType::sbreak) {
            cout<<"Smol break\n"<<endl;
            myfile<<"Smol break\n"<<endl;
            actions(1, Student);
        }
    }
    cout<<"The day has passed! \n\n"<<endl;                                     ///и като свърши всичко, да пише че сме свършили деня
    myfile<<"The day has passed! \n\n"<<endl;
}

void big_break(queue <chas> &day, Subject &current_subject, TeacherType &current_type, int &current_hours) {   ///функция за голяма почивка
    chas TempClass;                                     ///правим един темп час
    TempClass.type = ChasType::bbreak;                  /// казваме му да е голяма почивка
    day.push(TempClass);                                ///пушваме го
    Subject new_subject = current_subject;              /// казваме на новия предмет да е като сегашния
    int rand_subject;
    while(new_subject == current_subject) {             ///и ако са еднакви, да генерира число от 0 до 3
        rand_subject = RandomNum(0,3);                  /// и според това, какво се падне , то да е новия предмет(помага за генерирането на ден/седмица като цяло)
        switch (rand_subject) {
            case 0 : current_subject = Subject::analysis;
                     break;
            case 1 : current_subject = Subject::algebra;
                     break;
            case 2 : current_subject = Subject::sdp;
                     break;
            case 3 : current_subject = Subject::custom;
                     break;
        }
    }
    int rand_teacher = RandomNum(0,1);                          /// мятаме монета, за да си избере дали ще е лекция или упражнение
    switch(rand_teacher) {
        case 0: current_type = TeacherType::lecturer;
                break;
        case 1: current_type = TeacherType::ta;
                break;
    }
    current_hours=0;
    return;
}


void small_break(queue <chas> &day, int &current_hours) {/// функция за малка почивка , просто я правим и я пушваме,
    chas TempClass;
    TempClass.type = ChasType::sbreak;
    day.push(TempClass);
    current_hours++;
}

void dupka(queue <chas> &day, int &hours, Subject &current_subject, TeacherType &current_type, int &current_hours) {/// тъй като и дупката е блок/обект, трябва да я направим като някакъв час
    chas TempClass;
    TempClass.type = ChasType::dupka;                                                                               ///реално никъде не я провеждаме като лекция, но по-добре така
    Subject new_subject = current_subject;                                                                          ///отколкото да си тровя нервите със отделен клас за дупка и т.н
    int rand_subject;
    while(new_subject == current_subject) {
        rand_subject = RandomNum(0,3);
        switch (rand_subject) {
            case 0 : current_subject = Subject::analysis;
                     break;
            case 1 : current_subject = Subject::algebra;
                     break;
            case 2 : current_subject = Subject::sdp;
                     break;
            case 3 : current_subject = Subject::custom;
                     break;
        }
    }

    int rand_teacher = RandomNum(0,1);
    switch(rand_teacher) {
        case 0: current_type = TeacherType::lecturer;
                break;
        case 1: current_type = TeacherType::ta;
                break;
    }
    current_hours=0;
    day.push(TempClass);
    hours--;
}

void work_hour(queue <chas> &day, Teacher *&Sustav, Subject current_subject, TeacherType type,int &hours) {///просто ни вика учителите от масива, вместо да подаваме 8 учителя навсякъде
    chas TempClass;                                                                                         ///основно се вика от други функции
    Teacher teacher;
    for(int i=0;i<8;i++) {
        if(Sustav[i].subject == current_subject && Sustav[i].type == type) {
            teacher = Sustav[i];
            break;
        }
    }
    TempClass.type = ChasType::work;
    TempClass.teacher = teacher;
    day.push(TempClass);
    hours--;

}

void make_day(queue <chas> &day, Hero &Student, Teacher *Sustav)    ///генерира цял учебен ден
{
    int hours = RandomNum(7,13);
    int current_hours = 0;
    Subject current_subject = Subject::analysis;
    TeacherType current_type = TeacherType::lecturer;
    int rand_subject = RandomNum(0,3);
    switch (rand_subject) {
        case 0 : current_subject = Subject::analysis;
                break;
        case 1 : current_subject = Subject::algebra;
                break;
        case 2 : current_subject = Subject::sdp;
                break;
        case 3 : current_subject = Subject::custom;
                break;
    }

    int rand_teacher = RandomNum(0,1);
    switch(rand_teacher) {
        case 0: current_type = TeacherType::lecturer;
                break;
        case 1: current_type = TeacherType::ta;
                break;
    }
    while(hours>0)///докато възможните ни часове не са свършили(генерираното число, което в другите функции намаляваме)
    {
        if(!(day.empty()) && day.back().type == ChasType::work && current_hours >= 2) {///ако деня е празен + посления предмет е час + повече от 2 часа на един предмет
            big_break(day, current_subject, current_type, current_hours);
        }
        else if(!(day.empty()) && day.back().type == ChasType::work && current_hours == 2) {    ///пак така, само че ако са точно 2 часа
            int rand_stop = RandomNum(0,1);
            switch(rand_stop) {                 ///мятаме монета и според нея правим голяма/малка почивка
                case 0: small_break(day, current_hours);
                break;
                case 1: big_break(day, current_subject, current_type, current_hours);
                break;
            }
        }
        else if(!(day.empty()) && day.back().type == ChasType::work) {
            small_break(day, current_hours);
        }
        else if(!(day.empty()) && day.back().type == ChasType::dupka) {
            work_hour(day, Sustav, current_subject, current_type, hours);
        }
        else {
            int rand_hour = RandomNum(0,4);///ако са над 3ч да прави дупка
            if(rand_hour > 3) {
                dupka(day, hours, current_subject, current_type, current_hours);
            }
            work_hour(day, Sustav, current_subject,current_type, hours);
        }
    }
}


int main()
{
    srand(time(0));
    Hero Student;
    queue <chas> day;
    myfile.open("log.txt"); ///отваря вече генерирания файл

    Teacher Sustav[8];///масива от учители

    Sustav[0] = EnterTeacher(Subject::analysis, TeacherType::lecturer);
    Sustav[1] = EnterTeacher(Subject::algebra, TeacherType::lecturer);
    Sustav[2] = EnterTeacher(Subject::sdp, TeacherType::lecturer);
    Sustav[3] = EnterTeacher(Subject::custom, TeacherType::lecturer);

    Sustav[4] = EnterTeacher(Subject::analysis, TeacherType::ta);
    Sustav[5] = EnterTeacher(Subject::algebra, TeacherType::ta);
    Sustav[6] = EnterTeacher(Subject::sdp, TeacherType::ta);
    Sustav[7] = EnterTeacher(Subject::custom, TeacherType::ta);

    int day_count=0;
    while(day_count < 5) {  ///5 дневна седмица(ако искаш повече смени 5цата)
        cout<< "-----------DAY " << day_count + 1 << " ----------- "<<endl;     /// всеки ден да се разпознава и +1 щото надали искаш нулев ден
        myfile<< "-----------DAY " << day_count + 1 << " ----------- "<<endl;
        make_day(day, Student, Sustav);                                 ///генерира ни деня

        PrintProgram(day);                                              /// пише всичко в него

        cout << endl;
        myfile << endl;
        LectureProcess(day, Student, Sustav);                       ///провежда си целия ден
        day_count++;                                                ///увеличав броя дни
    }

    myfile.close();                                     ///затваря файла, след като свърши цялото писане(може да го махнеш ако искаш)
}
