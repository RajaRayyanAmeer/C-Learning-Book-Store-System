#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Book
{
 public:
       string ISBN;
       string title;
       string author;
       double price;
       int quantity;
       string content;
       Book(string ISBN, string title, string author, double price, int quantity, string content)
	   {
        this->ISBN = ISBN;
        this->title = title;
        this->author = author;
        this->price = price;
        this->quantity = quantity;
        this->content = content;
       }
       void updateInventory(int quantity)
	   {
        this->quantity += quantity;
       }
       void displayBookInfo()
	   {
        cout<<" ISBN: "<<ISBN<<endl;
        cout<<" Title: "<<title<<endl;
        cout<<" Author: "<<author<<endl;
        cout<<" Price: $ "<<price<<endl;
        cout<<" Quantity: "<<quantity<<endl;
       }
};
class Cart
{
 public:
 vector<Book> books;
 double totalCost;
 Cart()
 {
  totalCost = 0.0;
 }
 void addBook(Book book, int quantity)
 {
  for (int i = 0; i < quantity; i++)
      {
       books.push_back(book);
       totalCost += book.price;
      }
 }
 void removeBook(Book book, int quantity, vector<Book>& inventory)
 {
  for (int i = 0; i < quantity; i++)
      {
       for (int j = 0; j < books.size(); j++)
	       {
            if (books[j].ISBN == book.ISBN)
			   {
                books.erase(books.begin() + j);
                totalCost -= book.price;
                for (int k = 0; k < inventory.size(); k++)
				    {
                     if (inventory[k].ISBN == book.ISBN)
					    {
                         inventory[k].updateInventory(1);
                         break;
                        }
                    }
                break;
               }
           }
      }
 }
 double calculateTotal()
 {
  return totalCost;
 }
};
class Store
{
 public:
       vector<Book> inventory;
       void addBook(Book book)
	   {
        inventory.push_back(book);
       }
       Book searchBookByISBN(string ISBN)
	   {
        ISBN.erase(0, ISBN.find_first_not_of(" "));
        ISBN.erase(ISBN.find_last_not_of(" ") + 1); 
        for (int i = 0; i < inventory.size(); i++)
		    {
             if (inventory[i].ISBN == ISBN)
			    {
                 return inventory[i];
                }
            }
        return Book("", "", "", 0.0, 0, "");
       }
       void displayAvailableBooks()
	   {
        for (int i = 0; i < inventory.size(); i++)
		    {
             inventory[i].displayBookInfo();
             cout<<endl;
            }
       }
       void checkout(Cart cart)
	   {
        for (int i = 0; i < cart.books.size(); i++)
		    {
             Book book = cart.books[i];
             for (int j = 0; j < inventory.size(); j++)
			     {
                  if (inventory[j].ISBN == book.ISBN)
				     {
                      inventory[j].updateInventory(-1);
                      break;
                     }
                 }
            }
       }
};
int main()
{
 Store store;
 Cart cart;
 store.addBook(Book("1234567890", "Book 1", "Author 1", 19.99, 100, "This is the content of Book 1"));
 store.addBook(Book("2345678901", "Book 2", "Author 2", 14.99, 100, "This is the content of Book 2"));
 store.addBook(Book("3456789012", "Book 3", "Author 3", 24.99, 100, "This is the content of Book 3"));
 cout<<" Welcome to the bookstore! "<<endl;
 while (true)
 {
  cout<<" 1. View all books. "<<endl;
  cout<<" 2. Add book to cart. "<<endl;
  cout<<" 3. Remove book from cart. "<<endl;
  cout<<" 4. Checkout. "<<endl;
  cout<<" 5. Read Online or Download. "<<endl;
  cout<<" 6. Exit. "<<endl;
  int choice;
  cin>>choice;
  switch (choice)
  {
   case 1:
          store.displayAvailableBooks();
          break;
   case 2:
         {
          string ISBN;
          cout<<" Enter the ISBN of the book you want to add to cart: ";
          cin>>ISBN;
          Book book = store.searchBookByISBN(ISBN);
          if (book.ISBN != "")
		     {
              int quantity;
              cout<<" Enter the quantity of the book you want to add to cart: ";
              cin>>quantity;
              if (book.quantity >= quantity)
			     {
                  cart.addBook(book, quantity);
                  for (int i = 0; i < store.inventory.size(); i++)
				      {
                       if (store.inventory[i].ISBN == book.ISBN)
					      {
                           store.inventory[i].quantity -= quantity;
                           break;
                          }
                      }
                  cout<<" Book added to cart successfully! "<<endl;
                 }
			  else
			      {
                   cout<<" Sorry, we don't have enough copies of this book in stock. "<<endl;
                  }
             }
		  else
		      {
               cout<<" Book not found. Please try again. "<<endl;
              }
          break;
         }
   case 3:
         {
          string ISBN;
          cout<<" Enter the ISBN of the book you want to remove from cart: ";
          cin>>ISBN;
          Book book = store.searchBookByISBN(ISBN);
          if (book.ISBN != "")
		     {
              int quantity;
              cout<<" Enter the quantity of the book you want to remove from cart: ";
              cin>>quantity;
              cart.removeBook(book, quantity, store.inventory);
              cout<<" Book removed from cart successfully! "<<endl;
             }
		  else
		      {
               cout<<" Book not found in cart. Please try again. "<<endl;
              }
          break;
         }
   case 4:
         {
          cout<<" Your cart: "<<endl;
          for (int i = 0; i < cart.books.size(); i++)
		      {
               cart.books[i].displayBookInfo();
               cout<<endl;
              }
          cout<<" Total cost: $ "<<cart.calculateTotal()<<endl;
          store.checkout(cart);
          cout<<" Checkout successful! Thank you for shopping with us. "<<endl;
          return 0;
         }
   case 5:
         {
          string ISBN;
          cout<<" Enter the ISBN of the book you want to read online or download: ";
          cin>>ISBN;
          Book book = store.searchBookByISBN(ISBN);
          if (book.ISBN != "")
		     {
              cout<<" Do you want to (1) read the book online or (2) download the book? "<<endl;
              int choice;
              cin>>choice;
              if (choice == 1)
			     {
                  cout<<" Reading the book online... "<<endl;
                  cout<<book.content<<endl;
                 }
			  else if (choice == 2)
			          {
                       cout<<" Downloading the book... "<<endl;
                       cout<<" Book downloaded successfully! "<<endl;
                      }
			  else
			      {
                   cout<<" Invalid choice. Please try again. "<<endl;
                  }
              }
		  else
		      {
               cout<<" Book not found. Please try again. "<<endl;
              }
          break;
         }
   case 6:
          return 0;
   default:
           cout<<" Invalid choice. Please try again. "<<endl;
  }
 }
 return 0;
}       