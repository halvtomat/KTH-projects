class OverviewView {
    constructor(container, model) {
        this.container = container;
        this.model = model;
    }
    render() {
        this.container.querySelector("#my_dinner").innerHTML ="My dinner: " + this.model.getNumberOfGuests() + " people";
        this.container.querySelector("#totalPrice_overview").innerHTML = "Total: SEK " + Math.round(this.model.getTotalMenuPrice()*100)/100;

        for(let i = 0; i < this.model.menu.length; i++){
            this.renderOverview(i,this.model);
        }
	this.afterRender();
    }

    afterRender() {
    }

    renderOverview(num, model){
        let overviewItem = document.createElement("overviewItem");
        let overviewItem_image = document.createElement("IMG");
        let overviewItem_title = document.createElement("overviewItem_title");
        let overviewItem_price = document.createElement("overviewItem_price");
        overviewItem.id = "overviewItem" + num;
        overviewItem_image.id = "overviewItem_image" + num;
        overviewItem_title.id = "overviewItem_title" + num;
        overviewItem_price.id = "overviewItem_price" + num;
        overviewItem.className = "overviewItem";
        overviewItem_image.className = "overviewItem_image";
        overviewItem_title.className = "overviewItem_title";
        overviewItem_price.className = "overviewItem_price";
        overviewItem_image.src = model.getFullMenu()[num].image;
        overviewItem_title.innerHTML = model.getFullMenu()[num].title;
        overviewItem_price.innerHTML = "SEK " + model.getFullMenu()[num].pricePerServing;
        overviewItem.appendChild(overviewItem_image);
        overviewItem.appendChild(overviewItem_title);
        overviewItem.appendChild(overviewItem_price);
        document.querySelector("#overview_middle_left").appendChild(overviewItem);
        overviewItem.style="grid-column" + (num+1);
    }
    
}
