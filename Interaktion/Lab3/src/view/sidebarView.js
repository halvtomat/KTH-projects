class SidebarView {
    constructor(container, model) {
      this.container = container;
      this.model = model;
      this.model.addObserver(this);
    }
    
    render() {
        
        this.container.querySelector("#guestNumberSelect").value = this.model.getNumberOfGuests();
        
        this.container.querySelector("#totalPrice").innerHTML = "SEK " + Math.round(this.model.getTotalMenuPrice()*100)/100;

        for(let i = 0; i < this.model.menu.length; i++){
            this.renderMenuItem(i,this.model);
        }
    }
    
    afterRender() {
        this.container.querySelector("#guestNumberSelect").addEventListener('input', () => {
            var value = this.container.querySelector("#guestNumberSelect").value;
            this.model.setNumberOfGuests(value);
            this.model.notifyObserver();
        }); 
    }

    update(){
        this.render();
    }
    renderMenuItem(num, model){
        let menuItem = document.createElement("menuItem");
        menuItem.id = "menuItem" + num;
        menuItem.className = "menuItem";
        menuItem.style= "grid-row:"+(num+1);
        let menuItem_title = document.createElement("menuItem_title");
        let menuItem_price = document.createElement("menuItem_price");
        menuItem_title.id = "menuItem_title" + num;
        menuItem_price.id  = "menuItem_price" + num;
        menuItem_title.className = "menuItem_title";
        menuItem_price.className = "menuItem_price";
        menuItem_title.innerHTML = model.getFullMenu()[num].title;
        menuItem_price.innerHTML = "SEK " + model.getFullMenu()[num].pricePerServing;
        menuItem.appendChild(menuItem_title);
        menuItem.appendChild(menuItem_price);
        document.querySelector("#sidebar_bottom").appendChild(menuItem);
        document.querySelector("#totalPrice").style="grid-row:"+(num+2);
        document.querySelector("#placeOrderBtn").style="grid-row:"+(num+3);
      }
  }
  