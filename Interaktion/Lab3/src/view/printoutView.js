class PrintoutView {
    constructor(container, model) {
      this.container = container;
      this.model = model;
    }
    render() {
        this.container.querySelector("#printout_top_text").innerHTML ="My dinner: " + this.model.getNumberOfGuests() + " people";

        for(let i = 0; i < this.model.menu.length; i++){
            this.renderPrintout(i,this.model);
        }
    }
    
    afterRender() {
    }

    renderPrintout(num, model){
        let printoutItem = document.createElement("printoutItem");
        let printoutItem_image = document.createElement("IMG");
        let printoutItem_title = document.createElement("printoutItem_title");
        let printoutItem_description = document.createElement("printoutItem_description")
        let printoutItem_preparation = document.createElement("printoutItem_preparation");
        let printoutItem_preparation_text = document.createElement("printoutItem_preparation_text");
        printoutItem.id = "printoutItem" + num;
        printoutItem_image.id = "printoutItem_image" + num;
        printoutItem_title.id = "printoutItem_title" + num;
        printoutItem_description.id = "printoutItem_description" + num;
        printoutItem_preparation.id = "printoutItem_preparation" + num;
        printoutItem_preparation_text.id = "printoutItem_preparation_text" + num;
        printoutItem.className = "printoutItem";
        printoutItem_image.className = "printoutItem_image";
        printoutItem_title.className = "printoutItem_title";
        printoutItem_description.className = "printoutItem_description";
        printoutItem_preparation.className = "printoutItem_preparation";
        printoutItem_preparation_text.className = "printoutItem_preparation_text";
        printoutItem_image.src = model.getFullMenu()[num].image;
        printoutItem_title.innerHTML = model.getFullMenu()[num].title;
        printoutItem_description.innerHTML = "Lorem ipsum dolor sit, amet consectetur adipisicing elit. Fugit nobis non vel vero pariatur ab odio quo error molestiae? Rerum, eligendi. Maxime,voluptates labore. Dolores repudiandae, quibusdam dignissimos exercitationem perferendis provident voluptatibus eum vel nemo nulla numquam consectetur nostrum nesciunt qui tenetur ab magni ducimus quo ratione. Dicta quod quidem animi magni";
        printoutItem_preparation.innerHTML = "Preparation";
        printoutItem_preparation_text.innerHTML = "Lorem ipsum dolor sit, amet consectetur adipisicing elit. Fugit nobis non vel vero pariatur ab odio quo error molestiae? Rerum, eligendi. Maxime,voluptates labore. Dolores repudiandae, quibusdam dignissimos exercitationem perferendis provident voluptatibus eum vel nemo nulla numquam consectetur nostrum nesciunt qui tenetur ab magni ducimus quo ratione. Dicta quod quidem animi magni";
        printoutItem.appendChild(printoutItem_image);
        printoutItem.appendChild(printoutItem_title);
        printoutItem.appendChild(printoutItem_description);
        printoutItem.appendChild(printoutItem_preparation);
        printoutItem.appendChild(printoutItem_preparation_text);
        document.querySelector("#printout_bottom").appendChild(printoutItem);
        printoutItem.style="grid-row" + (num+1)
      }
  }
  