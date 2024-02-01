#include <iostream>
#include <queue>
#include <string>

////////////////////////////////////////
struct Animal
{
    virtual std::string MakeNoise() const = 0;
};

////////////////////////////////////////
struct Dog : public Animal
{
private:
    std::string mName;

public:
    explicit Dog(const std::string& name): mName{name} {}
    std::string Name() const { return mName; }
    virtual std::string MakeNoise() const final override { return "Bark Bark"; }
};

////////////////////////////////////////
struct Cat : public Animal
{
private:
    std::string mName;

public:
    explicit Cat(const std::string& name): mName{name} {}
    std::string Name() const { return mName; }
    virtual std::string MakeNoise() const final override { return "Meoww"; }
};

////////////////////////////////////////
struct AnimalShelter
{
private:
    std::queue<Animal*> mAnimals;

public:
    void Enqueue(Animal* animal)
    {
        mAnimals.push(animal);
    }

    Animal* DequeueAny()
    {
        if (mAnimals.size()) {
            Animal* animal{ mAnimals.front() };
            mAnimals.pop();
            return animal;
        }
        return nullptr;
    }

    Dog* DequeueDog()
    {
        std::vector<Animal*> nonDogs;
        while (mAnimals.size()) {
            Animal* animal{ mAnimals.front() };
            mAnimals.pop();
            if (Dog* dog{ dynamic_cast<Dog*>(animal) }) {
                for (Animal* nonDog : nonDogs) {
                    mAnimals.push(nonDog);
                }
                return dog;
            }
            nonDogs.push_back(animal);
        }
        for (Animal* nonDog : nonDogs) {
            mAnimals.push(nonDog);
        }
        return nullptr;
    }

    Cat* DequeueCat()
    {
        std::vector<Animal*> nonCats;
        while (mAnimals.size()) {
            Animal* animal{ mAnimals.front() };
            mAnimals.pop();
            if (Cat* cat{ dynamic_cast<Cat*>(animal) }) {
                for (Animal* nonCat : nonCats) {
                    mAnimals.push(nonCat);
                }
                return cat;
            }
            nonCats.push_back(animal);
        }
        for (Animal* nonCat : nonCats) {
            mAnimals.push(nonCat);
        }
        return nullptr;
    }

    std::size_t Count() const { return mAnimals.size(); }
};

////////////////////////////////////////
int main()
{
    AnimalShelter shelter;
    shelter.Enqueue(new Dog("DA"));
    shelter.Enqueue(new Dog("DB"));
    shelter.Enqueue(new Dog("DC"));
    shelter.Enqueue(new Cat("CA"));
    shelter.Enqueue(new Cat("CB"));

    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Dog* dog{ shelter.DequeueDog() };
    if (dog) {
        std::cout << "Dog's name: " << dog->Name() << '\n';
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Cat* cat{ shelter.DequeueCat() };
    if (cat) {
        std::cout << "Cat's name: " << cat->Name() << '\n';
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Animal* animal{ shelter.DequeueAny() };
    if (animal) {
        std::cout << "Animal says: " << animal->MakeNoise() << '\n';
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Dog* anotherDog{ shelter.DequeueDog() };
    if (anotherDog) {
        std::cout << "Dog's name: " << dog->Name() << '\n';
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Cat* anotherCat{ shelter.DequeueCat() };
    if (anotherCat) {
        std::cout << "Cat's name: " << anotherCat->Name() << '\n';
    }
    else {
        std::cout << "Sorry, no cats left :(\n";
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';

    Animal* anotherAnimal{ shelter.DequeueAny() };
    if (anotherAnimal) {
        std::cout << "Animal says: " << anotherAnimal->MakeNoise() << '\n';
    }
    std::cout << "Shelter size: " << shelter.Count() << '\n';
}
