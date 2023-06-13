#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variable
// Product structure
typedef struct {
    int code;
    char name[50];
    char description[100];
    float unit_price;
    char brand[50];
    char model[50];
    int quantity;
    char date[20];
    char category[50];
} Product;

// Customer structure
typedef struct {
    int id;
    char name[50];
    char address[100];
    char email[50];
    char phone_number[20];
} Customer;

// Order structure
typedef struct {
    int order_number;
    char date[20];
    Customer customer;
    Product product;
    char status[20];
} Order;

// Doubly linked list node
typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

// Doubly linked list structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Managing Products
void addProduct(LinkedList* products);
void updateProduct(LinkedList* products, int code);
void removeProduct(LinkedList* products, int code);
void listProductsByName(LinkedList* products);
void listProductsByBrand(LinkedList* products);
void searchProductsByName(LinkedList* products, const char* name);
void searchProductsByCategory(LinkedList* products, const char* category);
void generateLowStockReport(LinkedList* products, int min_stock);

// Managing customers
void addCustomer(LinkedList* customers);
void updateCustomer(LinkedList* customers, int id);
void removeCustomer(LinkedList* customers, int id);
void listCustomers(LinkedList* customers);
void searchCustomerAndPrintPurchaseHistory(LinkedList* customers, LinkedList* orders,const char* name);

// Managing orders
void addOrder(LinkedList* orders, LinkedList* customers, LinkedList* products);
void updateOrderStatus(LinkedList* orders, int order_number, const char* new_status);
void listOrdersByCustomer(LinkedList* orders, int customer_id);
void listPendingOrders(LinkedList* orders);

// Functions doubly linked list operations
Node* createNode(void* data);
void insertNode(LinkedList* list, void* data);
void deleteNode(LinkedList* list, Node* node);
void freeList(LinkedList* list);

void initializeList(LinkedList* list);

//Read and Write dos .txt
void readProductsData(LinkedList* products);
void readCustomersData(LinkedList* customers);
void readOrdersData(LinkedList* orders);
void updateProductsData(LinkedList* products);
void updateCustomersData(LinkedList* customers);
void updateOrdersData(LinkedList* orders);



int main() {
    // Initialize linked lists for products, customers, and orders
    LinkedList products, customers, orders;
    products.head = NULL;
    products.tail = NULL;
    products.size = 0;
    customers.head = NULL;
    customers.tail = NULL;
    customers.size = 0;
    orders.head = NULL;
    orders.tail = NULL;
    orders.size = 0;

    // Initialize the linked lists
    initializeList(&products);
    initializeList(&customers);
    initializeList(&orders);

    // Load data from text files
    readProductsData(&products);
    readCustomersData(&customers);
    readOrdersData(&orders);

    // Prompt for user choice
    int choice;
    do {
        printf("=========== Online Electronics Store ===========\n");
        printf("1. Manage Products\n");
        printf("2. Manage Customers\n");
        printf("3. Manage Orders\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Product menu
                printf("=========== Product Management ===========\n");
                printf("1. Add Product\n");
                printf("2. Update Product\n");
                printf("3. Remove Product\n");
                printf("4. List Products by Name\n");
                printf("5. List Products by Brand\n");
                printf("6. Search Products by Name\n");
                printf("7. Search Products by Category\n");
                printf("8. Generate Low Stock Report\n");
                printf("0. Go Back\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        addProduct(&products);
                        break;
                    case 2:
                        printf("Enter the product code to update: ");
                        int code;
                        scanf("%d", &code);
                        updateProduct(&products, code);
                        break;
                    case 3:
                        printf("Enter the product code to remove: ");
                        scanf("%d", &code);
                        removeProduct(&products, code);
                        break;
                    case 4:
                        listProductsByName(&products);
                        break;
                    case 5:
                        listProductsByBrand(&products);
                        break;
                    case 6:
                        printf("Enter the product name to search: ");
                        char searchName[50];
                        scanf("%s", searchName);
                        searchProductsByName(&products, searchName);
                        break;
                    case 7:
                        printf("Enter the product category to search: ");
                        char searchCategory[50];
                        scanf("%s", searchCategory);
                        searchProductsByCategory(&products, searchCategory);
                        break;
                    case 8:
                        printf("Enter the minimum stock level: ");
                        int minStock;
                        scanf("%d", &minStock);
                        generateLowStockReport(&products, minStock);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 2:
                // Customer menu
                printf("=========== Customer Management ===========\n");
                printf("1. Add Customer\n");
                printf("2. Update Customer\n");
                printf("3. Remove Customer\n");
                printf("4. List Customers\n");
                printf("5. Search Customer and Print Purchase History\n");
                printf("0. Go Back\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        addCustomer(&customers);
                        break;
                    case 2:
                        printf("Enter the customer ID to update: ");
                        int id;
                        scanf("%d", &id);
                        updateCustomer(&customers, id);
                        break;
                    case 3:
                        printf("Enter the customer ID to remove: ");
                        scanf("%d", &id);
                        removeCustomer(&customers, id);
                        break;
                    case 4:
                        listCustomers(&customers);
                        break;
                    case 5:
                        printf("Enter the customer name to search: ");
                        char searchName[50];
                        scanf("%s", searchName);
                        searchCustomerAndPrintPurchaseHistory(&customers, &orders, searchName);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 3:
                // Order menu
                printf("=========== Order Management ===========\n");
                printf("1. Add Order\n");
                printf("2. Update Order Status\n");
                printf("3. List Orders by Customer\n");
                printf("4. List Pending Orders\n");
                printf("0. Go Back\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        addOrder(&orders, &customers, &products);
                        break;
                    case 2:
                        printf("Enter the order number to update: ");
                        int orderNumber;
                        scanf("%d", &orderNumber);
                        printf("Enter the new status: ");
                        char newStatus[20];
                        scanf("%s", newStatus);
                        updateOrderStatus(&orders, orderNumber, newStatus);
                        break;
                    case 3:
                        printf("Enter the customer ID: ");
                        int customerId;
                        scanf("%d", &customerId);
                        listOrdersByCustomer(&orders, customerId);
                        break;
                    case 4:
                        listPendingOrders(&orders);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 0:
                // Save Data
                updateProductsData(&products);
                updateCustomersData(&customers);
                updateOrdersData(&orders);
                // free allocated memory
                freeList(&products);
                freeList(&customers);
                freeList(&orders);
                printf("Exiting the application. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}


// Function to add a new product
void addProduct(LinkedList* products) {
    Product* newProduct = (Product*)malloc(sizeof(Product));

    // Pede detalhes
    printf("Enter the product code: ");
    scanf("%d", &(newProduct->code));
    printf("Enter the product name: ");
    scanf("%s", newProduct->name);
    printf("Enter the product description: ");
    scanf("%s", newProduct->description);
    printf("Enter the unit price: ");
    scanf("%f", &(newProduct->unit_price));
    printf("Enter the brand: ");
    scanf("%s", newProduct->brand);
    printf("Enter the model: ");
    scanf("%s", newProduct->model);
    printf("Enter the quantity in stock: ");
    scanf("%d", &(newProduct->quantity));
    printf("Enter the date of addition to the catalog: ");
    scanf("%s", newProduct->date);
    printf("Enter the category: ");
    scanf("%s", newProduct->category);

    insertNode(products, newProduct);
}

// Function update an existing product
void updateProduct(LinkedList* products, int code) {
    Node* current = products->head;
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        if (product->code == code) {
            // Pede detalhes
            printf("Enter the new product name: ");
            scanf("%s", product->name);
            printf("Enter the new product description: ");
            scanf("%s", product->description);
            printf("Enter the new unit price: ");
            scanf("%f", &(product->unit_price));
            printf("Enter the new brand: ");
            scanf("%s", product->brand);
            printf("Enter the new model: ");
            scanf("%s", product->model);
            printf("Enter the new quantity in stock: ");
            scanf("%d", &(product->quantity));
            printf("Enter the new date of addition to the catalog: ");
            scanf("%s", product->date);
            printf("Enter the new category: ");
            scanf("%s", product->category);

            printf("Product with code %d updated successfully.\n", code);
            return;
        }
        current = current->next;
    }

    printf("Product with code %d not found.\n", code);
}

// Function to remove a product
void removeProduct(LinkedList* products, int code) {
    Node* current = products->head;
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        if (product->code == code) {
            deleteNode(products, current);
            printf("Product with code %d removed successfully.\n", code);
            free(product);
            return;
        }
        current = current->next;
    }

    printf("Product with code %d not found.\n", code);
}

// Function to list all products alphabetically by name
void listProductsByName(LinkedList* products) {
    Node* current = products->head;
    if (current == NULL) {
        printf("No products available.\n");
        return;
    }

    printf("========== Products by Name ==========\n");
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        printf("Code: %d, Name: %s, Brand: %s, Price: %.2f\n",
               product->code, product->name, product->brand, product->unit_price);
        current = current->next;
    }
}

// Function to list all products alphabetically by brand
void listProductsByBrand(LinkedList* products) {
    Node* current = products->head;
    if (current == NULL) {
        printf("No products available.\n");
        return;
    }

    printf("========== Products by Brand ==========\n");
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        printf("Code: %d, Brand: %s, Name: %s, Price: %.2f\n",
               product->code, product->brand, product->name, product->unit_price);
        current = current->next;
    }
}

// Function to search products by name
void searchProductsByName(LinkedList* products, const char* name) {
    Node* current = products->head;
    if (current == NULL) {
        printf("No products available.\n");
        return;
    }

    printf("========== Search Results ==========\n");
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        if (strcmp(product->name, name) == 0) {
            printf("Code: %d, Name: %s, Brand: %s, Price: %.2f\n",
                   product->code, product->name, product->brand, product->unit_price);
        }
        current = current->next;
    }
}

// Function to search products by category
void searchProductsByCategory(LinkedList* products, const char* category) {
    Node* current = products->head;
    if (current == NULL) {
        printf("No products available.\n");
        return;
    }

    printf("========== Search Results ==========\n");
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        if (strcmp(product->category, category) == 0) {
            printf("Code: %d, Category: %s, Name: %s, Brand: %s, Price: %.2f\n",
                   product->code, product->category, product->name, product->brand, product->unit_price);
        }
        current = current->next;
    }
}

// Function to generate a report of products with low stock
void generateLowStockReport(LinkedList* products, int min_stock) {
    Node* current = products->head;
    if (current == NULL) {
        printf("No products available.\n");
        return;
    }

    FILE* reportFile = fopen("low_stock_report.txt", "w");
    if (reportFile == NULL) {
        printf("Failed to generate the low stock report.\n");
        return;
    }

    fprintf(reportFile, "========== Low Stock Report ==========\n");
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        if (product->quantity < min_stock) {
            fprintf(reportFile, "Product with ID %d is with low stock. Current stock: %d\n",
                    product->code, product->quantity);
        }
        current = current->next;
    }

    fclose(reportFile);
    printf("Low stock report generated successfully.\n");
}

// Function to add new order
void addOrder(LinkedList* orders, LinkedList* customers, LinkedList* products) {
    Order* newOrder = (Order*)malloc(sizeof(Order));

    // Pede detalhes
    printf("Enter the order number: ");
    scanf("%d", &(newOrder->order_number));
    printf("Enter the date: ");
    scanf("%s", newOrder->date);
    printf("Enter the customer ID: ");
    scanf("%d", &(newOrder->customer.id));

    // Find the customer in the customers list
    Node* customerNode = customers->head;
    while (customerNode != NULL) {
        Customer* customer = (Customer*)(customerNode->data);
        if (customer->id == newOrder->customer.id) {
            // Customer found
            newOrder->customer = *customer;
            break;
        }
        customerNode = customerNode->next;
    }

    // Check if the customer was found
    if (customerNode == NULL) {
        printf("Customer with ID %d not found. Order not added.\n", newOrder->customer.id);
        free(newOrder);
        return;
    }

    printf("Enter the product code: ");
    scanf("%d", &(newOrder->product.code));

    // Find the product in the products list
    Node* productNode = products->head;
    while (productNode != NULL) {
        Product* product = (Product*)(productNode->data);
        if (product->code == newOrder->product.code) {
            // Product found
            newOrder->product = *product;
            break;
        }
        productNode = productNode->next;
    }
    // Verificacao
    // Check if the product was found
    if (productNode == NULL) {
        printf("Product with code %d not found. Order not added.\n", newOrder->product.code);
        free(newOrder);
        return;
    }

    printf("Enter the order status: ");
    scanf("%s", newOrder->status);

    insertNode(orders, newOrder);
}

// Function to update the status of an existing order
void updateOrderStatus(LinkedList* orders, int order_number, const char* new_status) {
    Node* current = orders->head;
    while (current != NULL) {
        Order* order = (Order*)(current->data);
        if (order->order_number == order_number) {
            strncpy(order->status, new_status, sizeof(order->status));
            printf("Order with number %d updated successfully.\n", order_number);
            return;
        }
        current = current->next;
    }

    printf("Order with number %d not found.\n", order_number);
}

// Function to list all orders made by a customer
void listOrdersByCustomer(LinkedList* orders, int customer_id) {
    Node* current = orders->head;
    if (current == NULL) {
        printf("No orders available.\n");
        return;
    }

    printf("========== Orders by Customer ==========\n");
    while (current != NULL) {
        Order* order = (Order*)(current->data);
        if (order->customer.id == customer_id) {
            printf("Order Number: %d, Date: %s, Status: %s\n",
                   order->order_number, order->date, order->status);
        }
        current = current->next;
    }
}

// Function to list all orders with the status "pending"
void listPendingOrders(LinkedList* orders) {
    Node* current = orders->head;
    if (current == NULL) {
        printf("No orders available.\n");
        return;
    }

    printf("========== Pending Orders ==========\n");
    while (current != NULL) {
        Order* order = (Order*)(current->data);
        if (strcmp(order->status, "pending") == 0) {
            printf("Order Number: %d, Date: %s, Customer ID: %d, Product Code: %d\n",
                   order->order_number, order->date, order->customer.id, order->product.code);
        }
        current = current->next;
    }
}


// Function to add a new customer
void addCustomer(LinkedList* customers) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));

    // Prompt the user for the customer details
    printf("Enter the customer ID: ");
    scanf("%d", &(newCustomer->id));
    printf("Enter the customer name: ");
    scanf("%s", newCustomer->name);
    printf("Enter the customer address: ");
    scanf("%s", newCustomer->address);
    printf("Enter the customer email: ");
    scanf("%s", newCustomer->email);
    printf("Enter the customer phone number: ");
    scanf("%s", newCustomer->phone_number);

    insertNode(customers, newCustomer);
}

// Function to update an existing customer
void updateCustomer(LinkedList* customers, int id) {
    Node* current = customers->head;
    while (current != NULL) {
        Customer* customer = (Customer*)(current->data);
        if (customer->id == id) {
            // Prompt the user for the updated details
            printf("Enter the new customer name: ");
            scanf("%s", customer->name);
            printf("Enter the new customer address: ");
            scanf("%s", customer->address);
            printf("Enter the new customer email: ");
            scanf("%s", customer->email);
            printf("Enter the new customer phone number: ");
            scanf("%s", customer->phone_number);

            printf("Customer with ID %d updated successfully.\n", id);
            return;
        }
        current = current->next;
    }

    printf("Customer with ID %d not found.\n", id);
}

// Function to remove a customer
void removeCustomer(LinkedList* customers, int id) {
    Node* current = customers->head;
    while (current != NULL) {
        Customer* customer = (Customer*)(current->data);
        if (customer->id == id) {
            deleteNode(customers, current);
            printf("Customer with ID %d removed successfully.\n", id);
            free(customer);
            return;
        }
        current = current->next;
    }

    printf("Customer with ID %d not found.\n", id);
}

// Function to list all customers
void listCustomers(LinkedList* customers) {
    Node* current = customers->head;
    if (current == NULL) {
        printf("No customers available.\n");
        return;
    }

    printf("========== Customers ==========\n");
    while (current != NULL) {
        Customer* customer = (Customer*)(current->data);
        printf("ID: %d, Name: %s, Address: %s, Email: %s, Phone: %s\n",
               customer->id, customer->name, customer->address, customer->email, customer->phone_number);
        current = current->next;
    }
}

// Function to search for a customer by name and print their purchase history
void searchCustomerAndPrintPurchaseHistory(LinkedList* customers,  LinkedList* orders, const char* name) {
    Node* current = customers->head;
    if (current == NULL) {
        printf("No customers available.\n");
        return;
    }

    printf("========== Search Results ==========\n");
    while (current != NULL) {
        Customer* customer = (Customer*)(current->data);
        if (strcmp(customer->name, name) == 0) {
            printf("Customer ID: %d\n", customer->id);
            printf("Purchase History:\n");
            // Iterate through the orders to find the orders made by this customer
            Node* orderNode = orders->head;
            while (orderNode != NULL) {
                Order* order = (Order*)(orderNode->data);
                if (order->customer.id == customer->id) {
                    printf("Order Number: %d\n", order->order_number);
                }
                orderNode = orderNode->next;
            }
            return;
        }
        current = current->next;
    }

    printf("Customer with name %s not found.\n", name);
}


// Function to create a new node
Node* createNode(void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node into the doubly linked list
void insertNode(LinkedList* list, void* data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
}

// Function to delete a node from the doubly linked list
void deleteNode(LinkedList* list, Node* node) {
    if (node == list->head) {
        list->head = node->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    } else if (node == list->tail) {
        list->tail = node->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
    list->size--;
}

// Function to free the memory allocated for the doubly linked list
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}



void initializeList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}



// Function to read products data from products.txt file
void readProductsData(LinkedList* products) {
    FILE* file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Failed to open products.txt file.\n");
        return;
    }

    while (!feof(file)) {
        Product* product = (Product*)malloc(sizeof(Product));
        if (fscanf(file, "%d %s %s %f %s %s %d %s %s\n", &(product->code), product->name,
                   product->description, &(product->unit_price), product->brand,
                   product->model, &(product->quantity), product->date, product->category) == 9) {
            insertNode(products, product);
        } else {
            free(product);
        }
    }

    fclose(file);
}

// Function to read customers data from customers.txt file
void readCustomersData(LinkedList* customers) {
    FILE* file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("Failed to open customers.txt file.\n");
        return;
    }

    while (!feof(file)) {
        Customer* customer = (Customer*)malloc(sizeof(Customer));
        if (fscanf(file, "%d %s %s %s %s\n", &(customer->id), customer->name,
                   customer->address, customer->email, customer->phone_number) == 5) {
            insertNode(customers, customer);
        } else {
            free(customer);
        }
    }

    fclose(file);
}

// Function to read orders data from orders.txt file
void readOrdersData(LinkedList* orders) {
    FILE* file = fopen("orders.txt", "r");
    if (file == NULL) {
        printf("Failed to open orders.txt file.\n");
        return;
    }

    while (!feof(file)) {
        Order* order = (Order*)malloc(sizeof(Order));
        if (fscanf(file, "%d %s %d %d\n", &(order->order_number), order->date,
                   &(order->customer.id), &(order->product.code)) == 4) {
            insertNode(orders, order);
        } else {
            free(order);
        }
    }

    fclose(file);
}
// write no fim da products.txt
void updateProductsData(LinkedList* products) {
    FILE* file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Failed to open products.txt file for writing.\n");
        return;
    }

    Node* current = products->head;
    while (current != NULL) {
        Product* product = (Product*)(current->data);
        fprintf(file, "%d %s %s %.2f %s %s %d %s %s\n", product->code, product->name,
                product->description, product->unit_price, product->brand,
                product->model, product->quantity, product->date, product->category);
        current = current->next;
    }

    fclose(file);
}
// write no fim da customers.txt
void updateCustomersData(LinkedList* customers) {
    FILE* file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("Failed to open customers.txt file for writing.\n");
        return;
    }

    Node* current = customers->head;
    while (current != NULL) {
        Customer* customer = (Customer*)(current->data);
        fprintf(file, "%d %s %s %s %s\n", customer->id, customer->name,
                customer->address, customer->email, customer->phone_number);
        current = current->next;
    }

    fclose(file);
}

// write no fim da orders.txt
void updateOrdersData(LinkedList* orders) {
    FILE* file = fopen("orders.txt", "w");
    if (file == NULL) {
        printf("Failed to open orders.txt file for writing.\n");
        return;
    }

    Node* current = orders->head;
    while (current != NULL) {
        Order* order = (Order*)(current->data);
        fprintf(file, "%d %s %d %d\n", order->order_number, order->date,
                order->customer.id, order->product.code);
        current = current->next;
    }

    fclose(file);
}
