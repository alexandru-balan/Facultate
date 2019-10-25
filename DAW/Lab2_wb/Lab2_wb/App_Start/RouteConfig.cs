using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Lab2_wb
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "Concatenare",
                url: "concatenare/{param1}/{param2}",
                defaults: new { controller = "Example", action = "Concatenare", param1 = UrlParameter.Optional, param2 = UrlParameter.Optional }
            );

            routes.MapRoute(
                name: "Produs",
                url: "produs/{param1}/{param2}",
                defaults: new {controller = "Produs", action = "Product", param2 = UrlParameter.Optional}
            );

            routes.MapRoute(
               name: "Operatie",
               url: "operatie/{param1}/{param2}/{param3}",
               defaults: new {controller = "Example", action = "Operatie", param1 = UrlParameter.Optional, param2 = UrlParameter.Optional, param3 = UrlParameter.Optional}
            );

            routes.MapRoute(
                name: "Index",
                url:"student/index",
                defaults: new {controller = "Student", action = "Index"}
            );

            routes.MapRoute(
                name: "Show",
                url: "student/show/{id}",
                defaults: new {controller = "Student", action ="show", id = UrlParameter.Optional}
                );

            routes.MapRoute(
                name: "Create",
                url: "student/create/{id}/{name}/{group}",
                defaults: new {controller = "Student", action = "Create", id = UrlParameter.Optional, name = UrlParameter.Optional , group = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "Update",
                url: "student/update/{id}/{name}/{group}",
                defaults: new {controller = "Student", action = "Update", id = UrlParameter.Optional, name = UrlParameter.Optional, group = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "Delete",
                url: "student/delete/{id}",
                defaults: new {controller = "Student", action = "Delete", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "Telefon",
                url: "search/telefon/{telefon}",
                defaults: new { controller = "Search", action = "Telefon", telefon = UrlParameter.Optional },
                constraints: new { telefon = @"^(?!^.{10})([0-9])+" }
                );

            routes.MapRoute(
                name: "CNP",
                url: "search/cnp/{cnp}",
                defaults: new { controller = "Search", action = "CNP", cnp = UrlParameter.Optional },
                constraints: new {cnp = @"^[1,2,5,6](?!^.{13})([0-9])+" }
                );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );

           
        }
    }
}
