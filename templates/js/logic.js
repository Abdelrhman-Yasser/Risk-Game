$(document).ready(function(){

		/* no match error msg */
		/******************************************/
		$("#no_match_msg").hide();

		/* setup form actions */
		$('#add_to_cart_form').attr('action', '/home/add_to_cart');
		$('#add_to_cart_form').attr('method', 'POST');

		/* website logo */
		/******************************************/
		var src_url = "https://www.momdeals.com/vfiles/25-7b9c2f40aedba2587b86dad83e58312f.png";
		//var src_url = "/../../resources/images/logo.png";
		$("#logo_image").attr("src", src_url);
		$("#logo_image").attr("height", "60");
		$("#logo_image").attr("width", "200");
		$("#logo_image").css( 'cursor', 'pointer' );
	
		/* hide modal events */
		/******************************************/
		$("#search_modal").hide();
		$("#view_book_modal").hide();
		var search_modal = document.getElementById('search_modal');
		var view_book_modal = document.getElementById('view_book_modal');
		window.onclick = function(event) {
		  if (event.target == search_modal) {
		    $("#search_modal").hide();
		    return;
		  }
		  if (event.target == view_book_modal) {
		    $("#view_book_modal").hide();
		    return;
		  }

		}

		/* view table rows */
		/******************************************/
		/* update rows AJAX */
		var data_url = "http://127.0.0.1:8081/home/refresh_table";
	    $.get(data_url, function(data, status){
	    	
	    	// obtain data
	    	book_list = JSON.parse(data);
	    	update_books_view();
	    });

	    /* personalized views */
		/******************************************/
		/* update rows AJAX */
		var data_url2 = "http://127.0.0.1:8081/home/update_views";
	    $.get(data_url2, function(data, status){
	    	
	    	// obtain data
	    	var personal_views = JSON.parse(data);
	    	$("#display_user_name").text(personal_views['user_name']);
	    	if(personal_views['credentials'] == 0){
	    		$("#admin_controls").remove();
	    	}else{
	    		$("#admin_controls").show();
	    	}

	    });

	    /* search form */
		/******************************************/
	    $('#search_btn').click(function(e){
	    	$('.table_data').remove();
	    	$("#search_modal").hide();

	    	var term = $("#search_term").val();
	    	var criteria = $("#search_criteria").val();
	    	var send_data = { search_term : term, search_criteria : criteria};
	    	var target_url = "http://127.0.0.1:8081/home/search";

			$.post(target_url, send_data, function(data, status){
				// obtain data
		    	book_list = JSON.parse(data);
		    	update_books_view();
			});
			$('#page_title').text("Search Result");
		});

	    /* handle site navigation */
		/******************************************/
	    $("#logo_image").click(function(e){
			var target_url = "http://127.0.0.1:8081/home";
  			$( location ).attr("href", target_url);
		});
		$("#account_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/account";
  			$( location ).attr("href", target_url);
		});
		$("#cart_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/cart";
  			$( location ).attr("href", target_url);
		});
		$("#my_orders_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/my_orders";
  			$( location ).attr("href", target_url);
		});
		$("#signout_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/signout";
  			$( location ).attr("href", target_url);
		});

		$("#manage_inventory_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/manage_inventory";
  			$( location ).attr("href", target_url);
		});
		$("#manage_publishers_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/manage_publishers";
  			$( location ).attr("href", target_url);
		});
		$("#publisher_orders_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/publisher_orders";
  			$( location ).attr("href", target_url);
		});
		$("#user_accounts_btn").click(function(e){
			var target_url = "http://127.0.0.1:8081/user_accounts";
  			$( location ).attr("href", target_url);
		});

	});


	/*******************************
	left outside for scoping purpose
	********************************/

	/* update view modal fields */
	/******************************************/
	function show_view_book_modal(book_index)
	{
		$("#book_isbn").val(book_list[book_index]["isbn"]);
		$("#book_title").val(book_list[book_index]["title"]);
		$("#book_author").val(book_list[book_index]["author"]);
		$("#book_publisher").val(book_list[book_index]["name"]);
		$("#book_category").val(book_list[book_index]["category_name"]);
		$("#book_price").val(book_list[book_index]["price"]);
		$("#book_year").val(book_list[book_index]["year"]);

		$('#view_book_modal').show();
	}


	function update_books_view()
	{
		$("#no_match_msg").hide();
		if(book_list.length == 0){
			$("#no_match_msg").show();
		}
		var i;
    	for(i=0; i<book_list.length; i++)
    	{
    		var tmp_book = book_list[i];
    		var title = tmp_book["title"];
    		var price = tmp_book["price"];

    		var view_btn = "<button class='w3-right' onclick='show_view_book_modal("+i+")'>view</button>";
    		var new_row = "<tr class='table_data'><td>"+title+"</td><td>"+price+"</td><td>"+view_btn+"</td></tr>";

    		$("#book_table > tbody").append(new_row);
    	}
	}